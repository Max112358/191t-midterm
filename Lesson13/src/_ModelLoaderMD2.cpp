// _ModelLoaderMD2.cpp
#include "_ModelLoaderMD2.h"
#include <cstring>
#include <iostream>

_ModelLoaderMD2::_ModelLoaderMD2() {
    pos = {0, 4, -100};
    dirAngleZ = 0;
    scale = {0.1f, 0.1f, 0.1f};  // Default scale
    currentState = ANIM_STAND;
    currentFrame = 0;
    interpValue = 0;
    myTex = new _TextureLoader();

    initAnimationRanges();

    // Initialize normal vectors table
    const vec3_t normals[162] = {
        #include "Anorms.h"
    };
    memcpy(anorms_table, normals, sizeof(anorms_table));
}

_ModelLoaderMD2::~_ModelLoaderMD2() {
    FreeModel(&md2file);
    delete myTex;
}

void _ModelLoaderMD2::initAnimationRanges() {
    animationRanges[ANIM_STAND]  = {0, 39, 6.0f};
    animationRanges[ANIM_RUN]    = {40, 45, 8.0f};
    animationRanges[ANIM_JUMP]   = {66, 71, 6.0f};
    animationRanges[ANIM_ATTACK] = {46, 53, 6.0f};
    animationRanges[ANIM_SALUTE] = {54, 60, 6.0f};
    animationRanges[ANIM_WAVE]   = {61, 65, 6.0f};
    animationRanges[ANIM_CROUCH] = {72, 75, 6.0f};
    animationRanges[ANIM_DEATH]  = {76, 86, 6.0f};
}

void _ModelLoaderMD2::setAnimationState(AnimationState state) {
    if (currentState != state) {
        currentState = state;
        currentFrame = animationRanges[state].startFrame;
        interpValue = 0.0f;
    }
}

void _ModelLoaderMD2::updateAnimation(float deltaTime) {
    const AnimationRange& range = animationRanges[currentState];
    interpValue += range.speed * deltaTime;

    if (interpValue >= 1.0f) {
        interpValue = 0.0f;
        currentFrame++;
        if (currentFrame >= range.endFrame) {
            currentFrame = range.startFrame;
        }
    }
}

bool _ModelLoaderMD2::initModel(const char* filename) {
    if (!ReadMD2Model(filename, &md2file)) {
        std::cout << "Failed to load MD2 model: " << filename << std::endl;
        return false;
    }
    return true;
}

void _ModelLoaderMD2::Draw() {
    glPushMatrix();
    glScalef(0.1f, 0.1f, 0.1f);  // Restore default scale for main character
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(-90.0f, 1.0, 0.0, 0.0);
    glRotatef(dirAngleZ, 0.0, 0.0, 1.0);

    RenderFrameItpWithGLCmds(currentFrame, interpValue, &md2file);
    glPopMatrix();
}

int _ModelLoaderMD2::ReadMD2Model(const char* filename, struct md2_model_t* mdl) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        std::cerr << "Error: couldn't open \"" << filename << "\"!\n";
        return 0;
    }

    // Read header
    fread(&mdl->header, 1, sizeof(struct md2_header_t), fp);

    if ((mdl->header.ident != 844121161) || (mdl->header.version != 8)) {
        std::cerr << "Error: bad version or identifier\n";
        fclose(fp);
        return 0;
    }

    // Allocate memory
    mdl->skins = new md2_skin_t[mdl->header.num_skins];
    mdl->texcoords = new md2_texCoord_t[mdl->header.num_st];
    mdl->triangles = new md2_triangle_t[mdl->header.num_tris];
    mdl->frames = new md2_frame_t[mdl->header.num_frames];
    mdl->glcmds = new int[mdl->header.num_glcmds];

    // Read data
    fseek(fp, mdl->header.offset_skins, SEEK_SET);
    fread(mdl->skins, sizeof(md2_skin_t), mdl->header.num_skins, fp);

    fseek(fp, mdl->header.offset_st, SEEK_SET);
    fread(mdl->texcoords, sizeof(md2_texCoord_t), mdl->header.num_st, fp);

    fseek(fp, mdl->header.offset_tris, SEEK_SET);
    fread(mdl->triangles, sizeof(md2_triangle_t), mdl->header.num_tris, fp);

    fseek(fp, mdl->header.offset_glcmds, SEEK_SET);
    fread(mdl->glcmds, sizeof(int), mdl->header.num_glcmds, fp);

    // Read frames
    fseek(fp, mdl->header.offset_frames, SEEK_SET);
    for (int i = 0; i < mdl->header.num_frames; ++i) {
        mdl->frames[i].verts = new md2_vertex_t[mdl->header.num_vertices];
        fread(mdl->frames[i].scale, sizeof(vec3_t), 1, fp);
        fread(mdl->frames[i].translate, sizeof(vec3_t), 1, fp);
        fread(mdl->frames[i].name, sizeof(char), 16, fp);
        fread(mdl->frames[i].verts, sizeof(md2_vertex_t), mdl->header.num_vertices, fp);
    }

    // Load appropriate texture based on model type
    if(strstr(filename, "Tekk") != nullptr) {
        myTex->loadTexture("models/Tekk/blade.jpg");
    }
    else if(strstr(filename, "carrot") != nullptr) {
        myTex->loadTexture("models/carrot/skin.jpg");
    }
    else if(strstr(filename, "MarvinMartian") != nullptr) {
        myTex->loadTexture("models/MarvinMartian/skin.jpg");
    }
    else {
        myTex->loadTexture(mdl->skins[0].name);
    }
    mdl->tex_id = myTex->tex;

    fclose(fp);
    return 1;
}

void _ModelLoaderMD2::RenderFrameItpWithGLCmds(int n, float interp, const struct md2_model_t* mdl) {
    glBindTexture(GL_TEXTURE_2D, mdl->tex_id);
    pglcmds = mdl->glcmds;

    int next_frame = (n + 1 >= animationRanges[currentState].endFrame) ?
                     animationRanges[currentState].startFrame : n + 1;

    while ((i = *(pglcmds++)) != 0) {
        if (i < 0) {
            glBegin(GL_TRIANGLE_FAN);
            i = -i;
        } else {
            glBegin(GL_TRIANGLE_STRIP);
        }

        for (; i > 0; --i, pglcmds += 3) {
            packet = (struct md2_glcmd_t*)pglcmds;
            pframe1 = &mdl->frames[n];
            pframe2 = &mdl->frames[next_frame];

            pvert1 = &pframe1->verts[packet->index];
            pvert2 = &pframe2->verts[packet->index];

            glTexCoord2f(packet->s, packet->t);

            n_curr = anorms_table[pvert1->normalIndex];
            n_next = anorms_table[pvert2->normalIndex];

            norm[0] = n_curr[0] + interp * (n_next[0] - n_curr[0]);
            norm[1] = n_curr[1] + interp * (n_next[1] - n_curr[1]);
            norm[2] = n_curr[2] + interp * (n_next[2] - n_curr[2]);

            glNormal3fv(norm);

            v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
            v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
            v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];

            v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
            v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
            v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];

            float t = interp * interp * (3 - 2 * interp);
            v[0] = v_curr[0] + t * (v_next[0] - v_curr[0]);
            v[1] = v_curr[1] + t * (v_next[1] - v_curr[1]);
            v[2] = v_curr[2] + t * (v_next[2] - v_curr[2]);

            glVertex3fv(v);
        }
        glEnd();
    }
}

void _ModelLoaderMD2::FreeModel(struct md2_model_t* mdl) {
    if (mdl->skins) {
        delete[] mdl->skins;
        mdl->skins = nullptr;
    }

    if (mdl->texcoords) {
        delete[] mdl->texcoords;
        mdl->texcoords = nullptr;
    }

    if (mdl->triangles) {
        delete[] mdl->triangles;
        mdl->triangles = nullptr;
    }

    if (mdl->glcmds) {
        delete[] mdl->glcmds;
        mdl->glcmds = nullptr;
    }

    if (mdl->frames) {
        for (int i = 0; i < mdl->header.num_frames; ++i) {
            delete[] mdl->frames[i].verts;
            mdl->frames[i].verts = nullptr;
        }
        delete[] mdl->frames;
        mdl->frames = nullptr;
    }
}

void _ModelLoaderMD2::writeInt(std::ofstream& file, int value) {
    file.write(reinterpret_cast<const char*>(&value), 4);
}

void _ModelLoaderMD2::writeShort(std::ofstream& file, short value) {
    file.write(reinterpret_cast<const char*>(&value), 2);
}

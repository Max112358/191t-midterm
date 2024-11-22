// _ModelLoaderMD2.h
#ifndef _MODELLOADERMD2_H
#define _MODELLOADERMD2_H

#include <_Common.h>
#include <_TextureLoader.h>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

typedef float vec3_t[3];

/* MD2 header */
struct md2_header_t {
    int ident;
    int version;
    int skinwidth;
    int skinheight;
    int framesize;
    int num_skins;
    int num_vertices;
    int num_st;
    int num_tris;
    int num_glcmds;
    int num_frames;
    int offset_skins;
    int offset_st;
    int offset_tris;
    int offset_frames;
    int offset_glcmds;
    int offset_end;
};

struct md2_skin_t {
    char name[64];
};

struct md2_texCoord_t {
    short s;
    short t;
};

struct md2_triangle_t {
    unsigned short vertex[3];
    unsigned short st[3];
};

struct md2_vertex_t {
    unsigned char v[3];
    unsigned char normalIndex;
};

struct md2_frame_t {
    vec3_t scale;
    vec3_t translate;
    char name[16];
    struct md2_vertex_t* verts;
};

struct md2_glcmd_t {
    float s;
    float t;
    int index;
};

struct md2_model_t {
    struct md2_header_t header;
    struct md2_skin_t* skins;
    struct md2_texCoord_t* texcoords;
    struct md2_triangle_t* triangles;
    struct md2_frame_t* frames;
    int* glcmds;
    GLuint tex_id;
};

class _ModelLoaderMD2 {
public:
    enum AnimationState {
        ANIM_STAND,
        ANIM_RUN,
        ANIM_JUMP,
        ANIM_ATTACK,
        ANIM_SALUTE,
        ANIM_WAVE,
        ANIM_CROUCH,
        ANIM_DEATH
    };

    struct AnimationRange {
        int startFrame;
        int endFrame;
        float speed;
    };

    _ModelLoaderMD2();
    virtual ~_ModelLoaderMD2();

    bool initModel(const char* filename);
    void Draw();
    void setAnimationState(AnimationState state);
    void updateAnimation(float deltaTime);
    void generateUVTemplate(const char* outputPath);

    void DrawWithScale(float scale) {
        glPushMatrix();
        glScalef(scale, scale, scale);
        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(-90.0f, 1.0, 0.0, 0.0);
        glRotatef(dirAngleZ, 0.0, 0.0, 1.0);

        RenderFrameItpWithGLCmds(currentFrame, interpValue, &md2file);
        glPopMatrix();
    }

    vec3 scale;  // Add scale property
    vec3 pos;
    float dirAngleZ;

private:
    int ReadMD2Model(const char* filename, struct md2_model_t* mdl);
    void FreeModel(struct md2_model_t* mdl);
    void RenderFrameItpWithGLCmds(int n, float interp, const struct md2_model_t* mdl);
    void initAnimationRanges();
    void writeInt(std::ofstream& file, int value);
    void writeShort(std::ofstream& file, short value);

    _TextureLoader* myTex;
    md2_model_t md2file;

    AnimationState currentState;
    std::map<AnimationState, AnimationRange> animationRanges;
    int currentFrame;
    float interpValue;

    // Rendering helpers
    GLfloat s, t;
    int i;
    vec3_t v_curr, v_next, v, norm;
    float *n_curr, *n_next;
    struct md2_frame_t *pframe, *pframe1, *pframe2;
    struct md2_vertex_t *pvert, *pvert1, *pvert2;
    struct md2_glcmd_t *packet;
    int *pglcmds;

    // Precalculated normal vectors
    vec3_t anorms_table[162];
};

#endif // _MODELLOADERMD2_H

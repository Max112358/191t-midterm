#include "_OBJLoader.h"

// Global function pointer definitions
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;

_OBJLoader::_OBJLoader() {
    pos = {0, 0, 0};
    rotation = {0, 0, 0};
    scale = {1, 1, 1};
    texture = new _TextureLoader();
}

_OBJLoader::~_OBJLoader() {
    cleanupModel();
}



bool _OBJLoader::loadModel(const char* path) {
    std::ifstream file(path);
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
        else if (prefix == "vt") {
            TextureCoord uv;
            iss >> uv.u >> uv.v;
            uvs.push_back(uv);
        }
        else if (prefix == "vn") {
            Normal normal;
            iss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (prefix == "f") {
            Face face;
            std::string vertex1, vertex2, vertex3;
            iss >> vertex1 >> vertex2 >> vertex3;

            // Parse vertex indices using sscanf for more reliable parsing
            sscanf(vertex1.c_str(), "%d/%d/%d",
                   &face.vertexIndex[0], &face.uvIndex[0], &face.normalIndex[0]);
            sscanf(vertex2.c_str(), "%d/%d/%d",
                   &face.vertexIndex[1], &face.uvIndex[1], &face.normalIndex[1]);
            sscanf(vertex3.c_str(), "%d/%d/%d",
                   &face.vertexIndex[2], &face.uvIndex[2], &face.normalIndex[2]);

            // Adjust indices to 0-based
            for(int i = 0; i < 3; i++) {
                face.vertexIndex[i]--;
                face.uvIndex[i]--;
                face.normalIndex[i]--;
            }
            faces.push_back(face);
        }
    }

    return true;
}


void _OBJLoader::renderModel() {
    glPushMatrix();

    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rotation.x, 1, 0, 0);
    glRotatef(rotation.y, 0, 1, 0);
    glRotatef(rotation.z, 0, 0, 1);
    glScalef(scale.x, scale.y, scale.z);

    glDisable(GL_COLOR_MATERIAL);
    float matte[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, matte);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);

    glBegin(GL_TRIANGLES);
    for (const Face& face : faces) {
        for (int i = 0; i < 3; i++) {
            if (face.normalIndex[i] < normals.size()) {
                glNormal3f(normals[face.normalIndex[i]].x,
                          normals[face.normalIndex[i]].y,
                          normals[face.normalIndex[i]].z);
            }

            if (face.uvIndex[i] < uvs.size()) {
                glTexCoord2f(uvs[face.uvIndex[i]].u,
                            uvs[face.uvIndex[i]].v);
            }

            if (face.vertexIndex[i] < vertices.size()) {
                glVertex3f(vertices[face.vertexIndex[i]].x,
                          vertices[face.vertexIndex[i]].y,
                          vertices[face.vertexIndex[i]].z);
            }
        }
    }
    glEnd();

    glEnable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void _OBJLoader::cleanupModel() {
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &uvVBO);
    glDeleteBuffers(1, &normalVBO);
    vertices.clear();
    uvs.clear();
    normals.clear();
    faces.clear();
}

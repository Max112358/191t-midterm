#ifndef _OBJLOADER_H
#define _OBJLOADER_H

#include <_Common.h>
#include <_TextureLoader.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Vertex {
    float x, y, z;
};

struct TextureCoord {
    float u, v;
};

struct Normal {
    float x, y, z;
};

struct Face {
    int vertexIndex[3];
    int uvIndex[3];
    int normalIndex[3];
};

class _OBJLoader {
public:
    _OBJLoader();
    virtual ~_OBJLoader();

    bool loadModel(const char* path);
    void renderModel();
    void cleanupModel();

    vec3 pos;
    vec3 rotation;
    vec3 scale;

private:
    std::vector<Vertex> vertices;
    std::vector<TextureCoord> uvs;
    std::vector<Normal> normals;
    std::vector<Face> faces;

    _TextureLoader* texture;
    GLuint vertexVBO;
    GLuint uvVBO;
    GLuint normalVBO;
};

#endif

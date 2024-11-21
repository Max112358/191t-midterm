#ifndef _COMMON_H
#define _COMMON_H

#include <string.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <cmath>

#ifdef _WIN64
typedef signed long long int GLsizeiptr;
#else
typedef ptrdiff_t GLsizeiptr;
#endif

// Function pointers for OpenGL extensions
typedef void (APIENTRY * PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef void (APIENTRY * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (APIENTRY * PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint* buffers);

// Declare function pointers
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

// OpenGL constants if not defined
#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif

#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW 0x88E4
#endif

#define PI 3.1415926

typedef struct {
    float x;
    float y;
}vec2;

typedef struct {
    float x;
    float y;
    float z;
}vec3;

typedef struct {
    float r;
    float g;
    float b;
}col3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
}vec4;

using namespace std;

#endif // _COMMON_H

#ifndef _MODELS_H
#define _MODELS_H
#include <_Common.h>
#include <_TextureLoader.h>
#include <_Timer.h>

class _Models
{
    public:
        _Models();
        virtual ~_Models();

        GLfloat rotateX;
        GLfloat rotateY;
        GLfloat rotateZ;

        vec3 pos;
        col3 color;
        int dir = 1;

        _TextureLoader* myTex = new _TextureLoader();
        _Timer *myTime = new _Timer();
        GLvoid inintModel(char* fileName);
        GLvoid drawModel();
        GLvoid moveModel();

    protected:

    private:
};

#endif // _MODELS_H

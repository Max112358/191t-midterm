#ifndef _SKYBOX_H
#define _SKYBOX_H

#include <_Common.h>
#include <_TextureLoader.h>


class _SkyBox
{
    public:
        _SkyBox();
        virtual ~_SkyBox();

        _TextureLoader skyTex[6];

        float scale;
        float xMin, yMin, zMin, xMax, yMax, zMax;
        float xRotation, yRotation, zRotation;
        float xTranslate, yTranslate, zTranslate;


        void skyBoxInit();
        void drawSkyBox();


    protected:

    private:
};

#endif // _SKYBOX_H

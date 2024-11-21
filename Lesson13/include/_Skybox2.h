#ifndef _SKYBOX2_H
#define _SKYBOX2_H

#include <_Common.h>
#include <_TextureLoader.h>
#include <_Timer.h>

class _Skybox2
{
    public:
        _Skybox2();
        virtual ~_Skybox2();

        void skyBoxinit(char *);
        void skyBoxDraw();

        vec2 tMax;
        vec2 tMin;
        vec3 scale;
        vec3 trans;
        vec3 rot;

        _TextureLoader *tex = new _TextureLoader();

    protected:

    private:
};

#endif // _SKYBOX2_H

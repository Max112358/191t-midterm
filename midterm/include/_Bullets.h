#ifndef _BULLETS_H
#define _BULLETS_H
#include <_Common.h>
#include <_TextureLoader.h>
#include <_Timer.h>


class _Bullets
{
    public:
        _Bullets();
        virtual ~_Bullets();
        _TextureLoader* tex = new _TextureLoader();
        _Timer* myTime = new _Timer();

        vec3 pos;
        vec3 scale;
        vec3 des;
        vec3 src;
        float t = 0; // parameter for the path
        bool live = true;

        enum {READY,DEAD,SHOOT,HIT};

        void initBullet(char*);
        void drawBullet();
        void bulletAction();

        int actionTrigger;


    protected:

    private:
};

#endif // _BULLETS_H

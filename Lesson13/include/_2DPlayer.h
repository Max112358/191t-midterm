#ifndef _2DPLAYER_H
#define _2DPLAYER_H

#include <_Common.h>
#include <_TextureLoader.h>
#include <_Timer.h>


class _2DPlayer
{
    public:
        _2DPlayer();
        virtual ~_2DPlayer();

        _TextureLoader *tex = new _TextureLoader();
        _Timer *myTime = new _Timer();


        enum {STAND, WALKLEFT, WALKRIGHT, RUN, JUMP, ATTACK};

        void initPlayer(int,int,char*); // number of x,y frames and the file name
        void drawPLayer();
        void actions();

        vec3 plPos; // position of player
        vec3 plScl; //change player size
        int framesX, framesY;

        float xMax,yMax,xMin,yMin;
        vec3 vert[4];

        int actionTrigger;


    protected:

    private:
};

#endif // _2DPLAYER_H

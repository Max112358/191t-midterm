#include "_Bullets.h"

_Bullets::_Bullets()
{
    //ctor
}

_Bullets::~_Bullets()
{
    //dtor
}
void _Bullets::initBullet(char* filename)
{
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    t = 0;
    des.x = 0;
    des.y = 20;
    des.z = -50;

    src.x = 0;
    src.y = 0;
    src.z = 0;

    live = false;

}

void _Bullets::drawBullet()
{
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    if(live){
    glTranslatef(pos.x, pos.y, pos.z);
    glutSolidSphere(0.5, 20,20);
    }
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);

}

void _Bullets::bulletAction()
{
    switch(actionTrigger){
    case READY:

        pos.x = 0;
        pos.y = 0;
        pos.z = 0;

        src.x = 0;
        src.y = 0;
        src.z = 0;


        t = 0;
        live = false;
        break;
    case DEAD:
        live = false;
        t = 0;
        actionTrigger = 0;
        break;
    case SHOOT:
        if(live){
        if(clock()-myTime->startTime<70){
        if(t < 1){t += 0.001;} else {actionTrigger = READY;}

        pos.x = src.x + t*(des.x - src.x);
        pos.y = src.y + t*(des.y - src.y);
        pos.z = src.z + t*(des.z - src.z);
        src.x = pos.x;
        src.y = pos.y;
        src.z = pos.z;
        } else{
            myTime->startTime = clock();
        }

        }

        break;
    case HIT:
        //use this to show explosion any other action
        break;
    }
}

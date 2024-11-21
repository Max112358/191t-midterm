#include "_2DPlayer.h"

_2DPlayer::_2DPlayer()
{
    //ctor
}

_2DPlayer::~_2DPlayer()
{
    //dtor
}
void _2DPlayer::initPlayer(int x, int y, char* fileName)
{
    vert[0].x = -1.0;
    vert[0].y = -1.0;
    vert[0].z = -1.0;

    vert[1].x = 1.0;
    vert[1].y = -1.0;
    vert[1].z = -1.0;

    vert[2].x = 1.0;
    vert[2].y = 1.0;
    vert[2].z = -1.0;

    vert[3].x = -1.0;
    vert[3].y = 1.0;
    vert[3].z = -1.0;

    plPos.x = 0.0;
    plPos.y = -0.0;
    plPos.z = -10.0;

    plScl.x = 1;
    plScl.y = 1;
    plScl.z = 1;

    tex->loadTexture(fileName);

    framesX = x;
    framesY = y;

    actionTrigger = 0;
    myTime->startTime = clock();
    xMin = 0;
    yMax = 1.0/(float)framesY;
    xMax = 1.0/(float)framesX;
    yMin = (yMax - 1.0)/(float)framesY;

}

void _2DPlayer::drawPLayer()
{
    glPushMatrix();
    glTranslatef(plPos.x, plPos.y, plPos.z);
    glScalef(plScl.x, plScl.y, plScl.z);


    glColor3f(1.0,1.0,1.0);
    tex->bindTexture();

    glBegin(GL_QUADS);


        glTexCoord2f(xMin, yMax);
        glVertex3f(vert[0].x, vert[0].y, vert[0].z);
        glTexCoord2f(xMax, yMax);
        glVertex3f(vert[1].x, vert[1].y, vert[1].z);
        glTexCoord2f(xMax, yMin);
        glVertex3f(vert[2].x, vert[2].y, vert[2].z);
        glTexCoord2f(xMin, yMin);
        glVertex3f(vert[3].x, vert[3].y, vert[3].z);

    glEnd();

    glPopMatrix();
}

void _2DPlayer::actions()
{
    switch(actionTrigger){
    case STAND:

       // xMin=0;
        //xMax= 1.0/(float)framesX;
        yMax= 1.0/(float)framesY;
        yMin= yMax-1.0/(float)framesY;

        break;
    case WALKLEFT:
    if(clock() - myTime->startTime > 60){

       if(xMin < 1){
        xMax += 1.0/(float)framesX;
        xMin += 1.0/(float)framesX;

       } else {

            xMax = 0;
            xMin = 1.0/(float)framesX;


            if(yMax < 1){
                yMax += 1.0/(float)framesY;
                yMin += 1.0/(float)framesY;
            } else {
                yMax = 1.0/(float)framesY;
                yMin = 0.0/(float)framesY;
            }
        }

            myTime->startTime = clock();
    }


        break;
    case WALKRIGHT:

        if(clock() - myTime->startTime > 60){

            if(xMax < 1){
            xMax += 1.0/(float)framesX;
            xMin += 1.0/(float)framesX;
            } else {
                xMin = 0;
                xMax = 1.0/(float)framesX;

                if(yMax < 1){
                    yMax += 1.0/(float)framesY;
                    yMin += 1.0/(float)framesY;
                } else {
                    yMax = 1.0/(float)framesY;
                    yMin = 0.0/(float)framesY;
                }
            }
            myTime->startTime = clock();
        }


        break;
    case RUN:
        break;
    case JUMP:
        break;
    case ATTACK:
        break;

    }
}

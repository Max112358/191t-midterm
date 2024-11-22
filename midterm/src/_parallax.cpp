#include "_parallax.h"

_parallax::_parallax()
{
    //ctor
    xMax = 1.0;
    xMin = 0.0;
    yMin = 0.0;
    yMax = 1.0;
}

_parallax::~_parallax()
{
    //dtor
}
void _parallax::parallaxInit(char* fileName)
{
    parallaxBackground->loadTexture(fileName);

}

void _parallax::parallaxScroll(bool Auto, string dir, float speed)
{

    if(Auto){
        if(clock() - myTime->startTime > 70){

        if(dir == "up"){
            yMin += speed;
            yMax += speed;
        } else if (dir == "down"){
            yMin -= speed;
            yMax -= speed;
        } else if (dir == "left"){
            xMax -= speed;
            xMin -= speed;
        } else if(dir == "right"){
            xMax += speed;
            xMin += speed;
            }

        myTime->startTime = clock();
        } // end of timer
    } // end of if auto
}

void _parallax::parallaxDraw(float width, float height)
{
    glColor3f(1.0,1.0,1.0);
    parallaxBackground->bindTexture();

    glDisable(GL_LIGHTING);

    glBegin(GL_POLYGON);

        glTexCoord2f(xMin,yMin);
        glVertex3f(-width/height,1.0,-8.0);
        glTexCoord2f(xMax,yMin);
        glVertex3f(width/height,1.0,-8.0);
        glTexCoord2f(xMax,yMax);
        glVertex3f(width/height,-1.0,-8.0);
        glTexCoord2f(xMin,yMax);
        glVertex3f(-width/height,-1.0,-8.0);

    glEnd();

     glEnable(GL_LIGHTING);

}

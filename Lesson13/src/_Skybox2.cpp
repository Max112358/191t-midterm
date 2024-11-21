#include "_Skybox2.h"

_Skybox2::_Skybox2()
{
    //ctor
}

_Skybox2::~_Skybox2()
{
    //dtor
}


void _Skybox2::skyBoxinit(char* filename)
{
    tex->loadTexture(filename);

    scale.x = 200;
    scale.y = 100;
    scale.z = 200;

    rot.x=rot.y=rot.z=0;
    trans.x=trans.y=trans.z=0;

    tMax.x=tMax.y=1.0;
    tMin.x=tMin.y=0.0;
}

void _Skybox2::skyBoxDraw()
{
  glDisable(GL_LIGHTING); // depend on your skybox
     glTranslatef(trans.x,trans.y,trans.z);
     glRotatef(rot.x,1,0,0);
     glRotatef(rot.y,0,1,0);
     glRotatef(rot.z,0,0,1);

     glScalef(scale.x,scale.y,scale.z);


     tex->bindTexture();
     tMin.x= 1.0/4.0;
     tMax.x= 2.0/4.0;
     tMin.y= 1.0/3.0;
     tMax.y= 2.0/3.0;


     glBegin(GL_QUADS);
     glTexCoord2f(tMin.x,tMin.y);glVertex3f(-1.0,1.0,1.0);
     glTexCoord2f(tMax.x,tMin.y);glVertex3f( 1.0,1.0,1.0);
     glTexCoord2f(tMax.x,tMax.y);glVertex3f( 1.0,-1.0,1.0);
     glTexCoord2f(tMin.x,tMax.y);glVertex3f(-1.0,-1.0,1.0);


     // Back Wall
     tMin.x= 3.0/4.0;
     tMax.x= 4.0/4.0;
     tMin.y= 1.0/3.0;
     tMax.y= 2.0/3.0;
     glTexCoord2f(tMax.x,tMin.y);glVertex3f(-1.0,1.0,-1.0);
     glTexCoord2f(tMax.x,tMax.y);glVertex3f( -1.0,-1.0,-1.0);
     glTexCoord2f(tMin.x,tMax.y);glVertex3f( 1.0,-1.0,-1.0);
     glTexCoord2f(tMin.x,tMin.y);glVertex3f(1.0,1.0,-1.0);


     //top Wall
     tMin.x= 1.0/4.0;
     tMax.x= 2.0/4.0;
     tMin.y= 0.0/3.0;
     tMax.y= 1.0/3.0;
     glTexCoord2f(tMax.x,tMin.y);glVertex3f(1.0,1.0,-1.0);
     glTexCoord2f(tMax.x,tMax.y);glVertex3f(1.0,1.0,1.0);
     glTexCoord2f(tMin.x,tMax.y);glVertex3f(-1.0,1.0,1.0);
     glTexCoord2f(tMin.x,tMin.y);glVertex3f(-1.0,1.0,-1.0);

     //Bottom Wall
     tMin.x= 1.0/4.0;
     tMax.x= 2.0/4.0;
     tMin.y= 2.0/3.0;
     tMax.y= 3.0/3.0;
     glTexCoord2f(tMin.x,tMin.y);glVertex3f( -1.0,-1.0,1.0);
     glTexCoord2f(tMax.x,tMin.y);glVertex3f( 1.0,-1.0,1.0);
     glTexCoord2f(tMax.x,tMax.y);glVertex3f( 1.0,-1.0,-1.0);
     glTexCoord2f(tMin.x,tMax.y);glVertex3f( -1.0,-1.0,-1.0);


     //left Wall
     tMin.x= 0.0/4.0;
     tMax.x= 1.0/4.0;
     tMin.y= 1.0/3.0;
     tMax.y= 2.0/3.0;
     glTexCoord2f(tMin.x,tMin.y);glVertex3f(-1.0,1.0,-1.0);
     glTexCoord2f(tMax.x,tMin.y);glVertex3f(-1.0,1.0,1.0);
     glTexCoord2f(tMax.x,tMax.y);glVertex3f(-1.0,-1.0,1.0);
     glTexCoord2f(tMin.x,tMax.y);glVertex3f(-1.0,-1.0,-1.0);

     //Right Wall
     tMin.x= 2.0/4.0;
     tMax.x= 3.0/4.0;
     tMin.y= 1.0/3.0;
     tMax.y= 2.0/3.0;
     glTexCoord2f(tMax.x,tMin.y);glVertex3f( 1.0,1.0,-1.0);
     glTexCoord2f(tMax.x,tMax.y);glVertex3f( 1.0,-1.0,-1.0);
     glTexCoord2f(tMin.x,tMax.y);glVertex3f( 1.0,-1.0,1.0);
     glTexCoord2f(tMin.x,tMin.y);glVertex3f( 1.0,1.0, 1.0);
     glEnd();

     glEnable(GL_LIGHTING);
}

#include "_Camera.h"

_Camera::_Camera()
{
    //ctor

}

_Camera::~_Camera()
{
    //dtor
}

void _Camera::camInit()
{

    //initialize camera values
         eye.x = eye.y = 0;
         eye.z = 10.0;
         des.x = 0;
         des.y = 0;
         des.z = -10;
         upVec.x = upVec.z = 0;
         upVec.y = 1.0;

         zoom = sqrt(pow(des.x-eye.x, 2) + pow(des.y - eye.y, 2) + pow(des.z - eye.z, 2));
}

void _Camera::setUpCam()
{

    eye.x = des.x + zoom * cos(thetaY * PI/180.0) * sin(thetaX*PI/180.0);
    eye.y = des.y + zoom * sin(thetaY * PI/180.0);
    eye.z = des.z + zoom * cos(thetaY * PI/180.0) * cos(thetaX*PI/180.0);




    //setup camera with values
    gluLookAt(eye.x, eye.y, eye.z, des.x, des.y, des.z, upVec.x, upVec.y, upVec.z);
}



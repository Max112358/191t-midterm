#include "_KbMs.h"

_KbMs::_KbMs()
{
    //ctor

    prev_MouseX = 0;
    prev_MouseY = 0;

    prev_MouseX_Cam = 0;
    prev_MouseY_Cam = 0;
    mouseTranslation = false;
    mouseRotation = false;
}

_KbMs::~_KbMs()
{
    //dtor
}
void _KbMs::keyPress(_Models* model)
{
    switch(wParam){
    case VK_LEFT:
        model->rotateY += 1.0;
        break;

    case VK_RIGHT:
        model->rotateY -= 1.0;
        break;

        //to do VK_DOWN, VK_UP,
        //do z rotations
    }
}

void _KbMs::keyUp()
{
    switch(wParam){

        default: break;

    }
}

void _KbMs::mouseEvent(double x, double y)
{
    prev_MouseX = x;
    prev_MouseY = y;

    switch(wParam)
    {
    case MK_LBUTTON: // set translation flag
        mouseTranslation = true;
        break;
    case MK_RBUTTON: // set rotation  flag
        mouseRotation = true;
        break;
    case MK_MBUTTON:

        break;
    }


}

void _KbMs::mouseEventUp()
{
    mouseRotation = false;
    mouseTranslation = false;
}

void _KbMs::mouseWheel(_Models* mdl, double delta)
{
    mdl->pos.z += delta/100;
}

void _KbMs::mouseMove(_Models* mdl, double x, double y)
{
    if(mouseTranslation){
        mdl->pos.x += (x - prev_MouseX)/100.0;
        mdl->pos.y -= (y - prev_MouseY)/100.0;
    }
    // to do
    // apply for rotations
    prev_MouseX = x;
    prev_MouseY = y;
}


void _KbMs::moveBck(_parallax* prlx, float speed)
{
     switch(wParam){
    case VK_LEFT:
        prlx->xMax -= speed;
        prlx->xMin -= speed;
        break;

    case VK_RIGHT:
        prlx->xMin += speed;
        prlx->xMax += speed;
        break;

    }
}



void _KbMs::keyPress(_SkyBox* sky)
{
      switch(wParam){
    case VK_LEFT:
        //sky->yRotation += 0.2;
        break;

    case VK_RIGHT:
        //sky->yRotation -= 0.2;
        break;

    case VK_DOWN:
        //sky->xRotation += 0.2;
        break;
    case VK_UP:
        //sky->xRotation -= 0.2;
        break;


        //to do VK_DOWN, VK_UP,
        //do z rotations
    }
}
void _KbMs::keyPress(_ModelLoaderMD2* MD2) {
    switch(wParam) {
    case VK_LEFT:
        MD2->setAnimationState(_ModelLoaderMD2::ANIM_RUN);
        MD2->dirAngleZ = 180;
        break;

    case VK_RIGHT:
        MD2->setAnimationState(_ModelLoaderMD2::ANIM_RUN);
        MD2->dirAngleZ = 0;
        break;

    case VK_DOWN:
        MD2->setAnimationState(_ModelLoaderMD2::ANIM_CROUCH);
        break;

    case VK_UP:
        MD2->setAnimationState(_ModelLoaderMD2::ANIM_JUMP);
        break;

    case VK_SPACE:
        MD2->setAnimationState(_ModelLoaderMD2::ANIM_ATTACK);
        break;
    }
}

void _KbMs::keyUp(_ModelLoaderMD2* MD2) {
    MD2->setAnimationState(_ModelLoaderMD2::ANIM_STAND);
}



/**********************************************************************/


void _KbMs::mouseMove(_Skybox2*, double, double)
{

}


void _KbMs::mouseMove(_SkyBox* sky, double x, double y)
{

}

void _KbMs::keyPress(_Skybox2* sky)
{
    switch(wParam){
    case VK_LEFT:
        //sky->rot.y += 0.2;
        break;

    case VK_RIGHT:
        //sky->rot.y -= 0.2;
        break;

    case VK_DOWN:
        //sky->rot.x += 0.2;
        break;
    case VK_UP:
        //sky->rot.x -= 0.2;
        break;


        //to do VK_DOWN, VK_UP,
        //do z rotations
    }
}


void _KbMs::keyPress(_2DPlayer* pls)
{
    switch(wParam){
    case VK_LEFT:
        pls->actionTrigger = pls->WALKLEFT;
        break;

    case VK_RIGHT:
        pls->actionTrigger = pls->WALKRIGHT;
        break;

    case VK_DOWN:

        break;
    case VK_UP:

        break;
    }
}


void _KbMs::keyUp(_2DPlayer* pl)
{
    pl->actionTrigger = pl->STAND;
}



void _KbMs::keyPress(_Camera* cam)
{
    switch(wParam){
    case 0x41: //press key 'A'
        cam->thetaX += 1.0f;
        break;

    case 0x44: //press key 'D'
        cam->thetaX -= 1.0f;
        break;

    case 0x53: // pres key 'S'
        cam->thetaY -= 1.0f;
        break;
    case 0x57: //press key 'W'
        cam->thetaY += 1.0f;
        break;

    }

}

void _KbMs::mouseMove(_Camera* cam, double x, double y)
{

        cam->des.x += (x - prev_MouseX_Cam)/3.0;
        cam->des.y -= (y - prev_MouseY_Cam)/3.0;

    // to do
    // apply for rotations
    prev_MouseX_Cam = x;
    prev_MouseY_Cam = y;
}


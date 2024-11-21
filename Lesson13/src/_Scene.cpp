#include "_Scene.h"
#include <_lightSetup.h>
#include <_Models.h>
#include <_KbMs.h>
#include <_parallax.h>
#include <_SkyBox.h>
#include <_Skybox2.h>
#include <_Camera.h>
#include <_2DPlayer.h>
#include <_Bullets.h>
#include <_Collision.h>
#include <_ModelLoaderMD2.h>
#include <_OBJLoader.h>
#include "EnemyManager.h"




_Camera *cam = new _Camera();
_lightSetup *myLight = new _lightSetup();
//_Models *teapot = new _Models();
_KbMs *KbMs = new _KbMs();
_parallax *plx = new _parallax();
_SkyBox *sky = new _SkyBox();
_Skybox2 *sky2 = new _Skybox2();
//_2DPlayer *pl = new _2DPlayer();
_Bullets b[20];
_Collision *hit = new _Collision();
_ModelLoaderMD2 *mdl3D = new _ModelLoaderMD2();
EnemyManager* enemies = new EnemyManager();

_Scene::_Scene()
{

    //ctor
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

_Scene::~_Scene()
{
    //dtor
}
GLint _Scene::initGL()
{

    // Initialize OpenGL extension function pointers
    glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");

    if (!glGenBuffers || !glBindBuffer || !glBufferData || !glDeleteBuffers) {
        std::cout << "OpenGL extensions not supported!" << std::endl;
        return false;
    }

    glShadeModel(GL_SMOOTH); //for smooth render
    glClearColor(1,1,1,0); //background color
    glClearDepth(2.0f); // test on Depth layer
    glEnable(GL_DEPTH_TEST); //activate depth Test
    glDepthFunc(GL_LEQUAL); //Depth function type
    glEnable(GL_COLOR_MATERIAL);
    myLight->setLight(GL_LIGHT0); // setting my first lights

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    cam->camInit();

    glEnable(GL_TEXTURE_2D);
    //mdl3D->initModel("models/Tekk/tris.md2");
    //mdl3D->initModel("models/MarvinMartian/tris.md2");
    //teapot->inintModel("images/tex.jpg");
    plx->parallaxInit("images/bck.png");
    //sky->skyBoxInit();
    sky2->skyBoxinit("images/bk.png");


    mdl3D->initModel("models/Tekk/tris.md2");
    mdl3D->setAnimationState(_ModelLoaderMD2::ANIM_STAND);

    //pl->initPlayer(6,4,"images/player.png");

    for(int i = 0; i < 20; ++i){
        b[i].initBullet("no images");
    }

    // In _Scene.cpp, in initGL()
    enemies->initEnemy("models/carrot/tris.md2");  // The carrot model should have its texture path in the md2 file
    enemies->spawnEnemy(50, 4, -100); // Spawns enemy to the right
    //mdl3D->generateUVTemplate("carrot_template.png", &mdl3D->md2file);


    return true;

}

GLint _Scene::drawScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); //clearing matrices
    cam->setUpCam();

    wireFrame ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   // teapot->rotateX += 0.005;

    glPushMatrix();
    //teapot->moveModel();
    myLight->movingLight(GL_LIGHT0);
    //teapot->drawModel();
    glPopMatrix();

    /*
    glPushMatrix();
    glTranslatef(0,-10,1);
    glRotatef(90,1,0,0);
    glScalef(100,50,1.0);
   // plx->parallaxScroll(true, "left", 0.005);
    plx->parallaxDraw(screenWidth,screenHeight);
    glPopMatrix();
    */

    //this part controls the parallax background
    glPushMatrix();
    glTranslatef(0,-10,1);
    glRotatef(90,1,0,0);
    glScalef(100,50,1.0);

    plx->parallaxScroll(true, "right", 0.005); // Enable auto-scrolling left
    plx->parallaxDraw(screenWidth,screenHeight);
    glPopMatrix();

    /*
    glPushMatrix();
    for(int i = 0; i < 20; ++i){
        b[i].drawBullet();
        if(hit->isSphereCollision(b[i].pos, teapot->pos, 0.2,0.3,0.4)){
            //cout << "hit" << endl;
            if(teapot->color.r == 1){
                teapot->color.r = 0;
                teapot->color.g = 1; //exam maybe :) allow for collision on 3d model
            } else if(teapot->color.g == 1){
                teapot->color.g = 0;
                teapot->color.b = 1;
            } else if(teapot->color.b == 1){
                teapot->color.b = 0;
                teapot->color.r = 1;
            }

        }
        b[i].bulletAction();
    }

     glPopMatrix();
    */

    glPushMatrix();
    //sky->drawSkyBox();
    sky2->skyBoxDraw();
    glPopMatrix();


    float deltaTime = 1.0f/60.0f; // Or calculate actual deltaTime

    glPushMatrix();
    mdl3D->updateAnimation(deltaTime);
    mdl3D->Draw();
    glPopMatrix();

    glPushMatrix();
    enemies->updateEnemies();
    enemies->drawEnemies();
    glPopMatrix();

    glPushMatrix();
    glDisable(GL_LIGHTING);
    //pl->drawPLayer();
    //pl->actions();
    glEnable(GL_LIGHTING);
    glPopMatrix();



    return true;
}

GLvoid _Scene::resizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/height;

    glViewport(0,0,width,height); // helps set the view port and normalized device coordinates to window coordinates
    glMatrixMode(GL_PROJECTION); // specifies which matrix stack is targeted for the subsequent matrix operations (GL_Projection: applies subsequent matrix operations to the projection matrix stack)
    glLoadIdentity(); // replaces the current matrix with a identity matrix
    gluPerspective(45, aspectRatio, 0.1,3000); // set the aspect ratio to determine the field of view in the x direction as well as changing the z axis an Field of View
    glMatrixMode(GL_MODELVIEW); // Model view applies matrix operations to the model view matrix stack
    glLoadIdentity();

}

GLvoid _Scene::mouseMapping(int x, int y)
{
     screenWidth = GetSystemMetrics(SM_CXSCREEN);
     screenHeight = GetSystemMetrics(SM_CYSCREEN);

     GLint viewPort[4];
     GLdouble modelViewM[16];
     GLdouble projectionM[16];
     GLfloat winX, winY, winZ;


     float scale = 60*(screenWidth/screenHeight);

     glGetDoublev(GL_MODELVIEW_MATRIX,modelViewM);
     glGetDoublev(GL_PROJECTION_MATRIX,projectionM);
     glGetIntegerv(GL_VIEWPORT,viewPort);

     winX = (GLfloat)x;
     winY = (GLfloat)(viewPort[3]-y);
     glReadPixels(x,int(winY),1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winZ);

     mouseX = (GLfloat)(x-screenWidth/2.0)/scale;
     mouseY = (GLfloat)(screenHeight/2.0-y)/scale;
     mouseZ = -100;



     gluUnProject(winX,winY,winZ,modelViewM,projectionM,viewPort,&mouseX,&mouseY,&mouseZ);

}


int _Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
    case WM_KEYDOWN:
        switch(wParam) {
        case VK_LEFT:
            mdl3D->dirAngleZ = 180;
            mdl3D->setAnimationState(_ModelLoaderMD2::ANIM_RUN);
            mdl3D->pos.x -= 0.5f; // Adjust speed as needed
            break;
        case VK_RIGHT:
            mdl3D->dirAngleZ = 0;
            mdl3D->setAnimationState(_ModelLoaderMD2::ANIM_RUN);
            mdl3D->pos.x += 0.5f; // Adjust speed as needed
            break;
        case VK_SPACE:
            mdl3D->setAnimationState(_ModelLoaderMD2::ANIM_JUMP);
            break;
        }
        break;

    case WM_KEYUP:
        if(wParam == VK_LEFT || wParam == VK_RIGHT) {
            mdl3D->setAnimationState(_ModelLoaderMD2::ANIM_STAND);
        }
        break;
    }
    return 0;
}

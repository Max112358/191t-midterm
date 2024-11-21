#ifndef _SCENE_H
#define _SCENE_H

#include <_Common.h>
#include "_TextDisplay.h" // Add at top with other includes


class _Scene
{

    public:
        _Scene();
        virtual ~_Scene();

        GLint initGL(); //initializing the scene
        GLint drawScene(); //Render scene
        GLvoid resizeScene(GLsizei, GLsizei); // address window resize
        GLvoid mouseMapping(int,int);

        int winMsg(HWND, UINT, WPARAM, LPARAM);
        WPARAM wParam;

        bool wireFrame = false;

        float screenWidth, screenHeight;

        GLdouble mouseX;
        GLdouble mouseY;
        GLdouble mouseZ;

        int mouseClicks = 0;


    protected:

    private:
        _TextDisplay* textDisplay;
};

#endif // _SCENE_H

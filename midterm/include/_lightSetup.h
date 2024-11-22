#ifndef _LIGHTSETUP_H
#define _LIGHTSETUP_H

#include <_Common.h>

class _lightSetup
{
    public:
        _lightSetup();
        virtual ~_lightSetup();


        GLfloat light_ambient[4]; // Environment
        GLfloat light_diffuse[4]; // For shade
        GLfloat light_specular[4]; // To shine
        GLfloat light_position[4]; // light position

        GLfloat mat_ambient[4]; // material values
        GLfloat mat_diffuse[4];
        GLfloat mat_specular[4];
        GLfloat high_shininess[1];

        GLvoid setLight(GLenum);
        GLvoid movingLight(GLenum);
        float spin = 0; // value for light movement


    protected:

    private:
};

#endif // _LIGHTSETUP_H

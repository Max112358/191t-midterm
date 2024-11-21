#include "_lightSetup.h"

_lightSetup::_lightSetup()
{
    //ctor
}

_lightSetup::~_lightSetup()
{
    //dtor
}
GLvoid _lightSetup::setLight(GLenum light)
{

        glEnable(light);
        glEnable(GL_LIGHTING);


        light_ambient[0] = 0; // Environment
        light_ambient[1] = 0;
        light_ambient[2] = 0;
        light_ambient[3] = 1;

        light_diffuse[0] = 1; // For shade
        light_diffuse[1] = 1;
        light_diffuse[2] = 1;
        light_diffuse[3] = 1;

        light_specular[0] = 1; // To shine
        light_specular[1] = 1;
        light_specular[2] = 1;
        light_specular[3] = 1;


        light_position[0] = 2; // light position
        light_position[1] = 5;
        light_position[2] = 5;
        light_position[3] = 1;

        mat_ambient[0] = 0.7; // material values
        mat_ambient[1] = 0.7;
        mat_ambient[2] = 0.7;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.8;
        mat_diffuse[1] = 0.8;
        mat_diffuse[2] = 0.8;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 1;
        mat_specular[1] = 1;
        mat_specular[2] = 1;
        mat_specular[3] = 1;

        high_shininess[1] = 100.0;

}

GLvoid _lightSetup::movingLight(GLenum Light)
{
    spin += 0.5; // spinning  my light
    glPushMatrix(); // start grouping
        glRotated(spin,0,1,0); // rotate around y axis
        glLightfv(Light, GL_POSITION, light_position); // change light position
    glPopMatrix(); // end of grouping

}

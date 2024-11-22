#ifndef _TEXTURELOADER_H
#define _TEXTURELOADER_H

#include<_Common.h>
#include<SOIL.h>


class _TextureLoader
{
    public:
        _TextureLoader();
        virtual ~_TextureLoader();

        GLuint tex; //image buffer handler
        GLint width, height; // image demensions
        unsigned char* image;

        void loadTexture(char* fileName);
        void bindTexture();

    protected:

    private:
};

#endif // _TEXTURELOADER_H

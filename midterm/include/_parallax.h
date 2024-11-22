#ifndef _PARALLAX_H
#define _PARALLAX_H

#include <_Common.h>
#include <_TextureLoader.h>
#include <_Timer.h>

class _parallax
{
    public:
        _parallax();
        virtual ~_parallax();

        _TextureLoader *parallaxBackground = new _TextureLoader();

        _Timer *myTime = new _Timer();

        void parallaxInit(char*);
        void parallaxScroll(bool,string,float);
        void parallaxDraw(float,float);

        float xMax,xMin,yMin,yMax;



    protected:

    private:
};

#endif // _PARALLAX_H

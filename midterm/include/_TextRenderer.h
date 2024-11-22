#ifndef _TEXTRENDERER_H
#define _TEXTRENDERER_H

#include <_Common.h>
#include <string>

class _TextRenderer {
public:
    static void renderText(const char* text, int x, int y, float r, float g, float b) {
        // Save all attributes that we'll modify
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        // Save matrices and setup ortho projection
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, 800, 0, 600, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // Disable states that might interfere with text rendering
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);

        // Reset color material mode
        glDisable(GL_COLOR_MATERIAL);

        // Ensure we're in the right blending mode for text
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set text color
        glColor3f(r, g, b);

        // Position and render text
        glRasterPos2i(x, y);
        for (const char* c = text; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }

        // Restore all states
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        // Restore all attributes
        glPopAttrib();
    }

    static void renderText(const char* text, int x, int y) {
        // Default to white text
        renderText(text, x, y, 1.0f, 1.0f, 1.0f);
    }
};

#endif // _TEXTRENDERER_H

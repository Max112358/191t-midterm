#ifndef _TEXTRENDERER_H
#define _TEXTRENDERER_H

#include <_Common.h>
#include <string>

class _TextRenderer {
public:
    static void renderText(const char* text, int x, int y) {
        // Save matrices and setup ortho projection
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, 800, 0, 600, -1, 1);  // Use fixed screen size for now

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // Temporarily disable depth testing and textures
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);

        // Set color to white for visibility
        glColor3f(1.0f, 1.0f, 1.0f);

        // Position and render text
        glRasterPos2i(x, y);
        for (const char* c = text; *c != '\0'; c++) {
            // Use GLUT_BITMAP_TIMES_ROMAN_24 for larger text
            // Options are:
            // GLUT_BITMAP_8_BY_13
            // GLUT_BITMAP_9_BY_15
            // GLUT_BITMAP_TIMES_ROMAN_10
            // GLUT_BITMAP_TIMES_ROMAN_24  (largest built-in font)
            // GLUT_BITMAP_HELVETICA_10
            // GLUT_BITMAP_HELVETICA_12
            // GLUT_BITMAP_HELVETICA_18
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }

        // Restore states
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        // Restore matrices
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
};

#endif // _TEXTRENDERER_H

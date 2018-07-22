#include "drawer.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

void Drawer::draw_quad(
        double x1, double y1,
        double x2, double y2,
        double x3, double y3,
        double x4, double y4) {
    
    glBegin(GL_QUADS);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glVertex2d(x3, y3);
    glVertex2d(x4, y4);
    glEnd();
    
}
void Drawer::draw_tri(
        double x1, double y1,
        double x2, double y2,
        double x3, double y3) {
    
    glBegin(GL_TRIANGLES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glVertex2d(x3, y3);
    glEnd();
}

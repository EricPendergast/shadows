#include "world.h"

World::World(){}

// Only draws polygons. Uses world coordinates.
void World::draw() {
    glBegin(GL_QUADS);
    //glVertex2f(5, 5);
    //glVertex2f(50, 375);
    //glVertex2f(375, 375);
    //glVertex2f(375, 125);

    glVertex2f(450, 300);
    glVertex2f(400, 300);
    glVertex2f(400, 350);
    glVertex2f(450, 350);

    glVertex2f(300, 200);
    glVertex2f(300, 250);
    glVertex2f(350, 250);
    glVertex2f(350, 250);
    
    glVertex2f(0, 500);
    glVertex2f(400, 500);
    glVertex2f(400, 490);
    glVertex2f(0, 490);

    glEnd();
}


#include "world.h"

World::World() : shader("shaders/main.vert", "shaders/main.frag") {}

void World::render_with_shader() {
    glUseProgram(shader.get_handle());
    draw();
}

// Only draws polygons. Uses world coordinates.
void World::draw() {
    glBegin(GL_QUADS);
    //glVertex2f(5, 0);
    //glVertex2f(125, 375);
    //glVertex2f(375, 375);
    //glVertex2f(375, 125);
    
    glVertex2f(400, 300);
    glVertex2f(400, 350);
    glVertex2f(450, 350);
    glVertex2f(450, 300);
    
    glEnd();
}

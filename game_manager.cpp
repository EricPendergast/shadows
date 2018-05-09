#include "game_manager.h"

void GameManager::display(void) {
    light->cast_shadows(*world, OpenGLContext::render_width, OpenGLContext::render_height, *casted_shadows);

    casted_shadows->copy_to(0);
    
    main_shader->use();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    world->draw();
    
    player.move(move_right - move_left, false);
    player.draw();
}

void GameManager::mouse_move(int x, int y) {
    light->light_x = (float)x;
    light->light_y = (float)y;
}

void GameManager::init_after_opengl_context() {
    main_shader = new ShaderProgram("shaders/main.vert", "shaders/main.frag");
    light = new Light();
    world = new World();
    casted_shadows = new BasicBuffer(OpenGLContext::render_width, OpenGLContext::render_height);
}


void GameManager::key_up(unsigned char key, int x, int y) {
    if (key == 'd')
        move_right = false;
    if (key == 'a')
        move_left = false;
}

void GameManager::key_down(unsigned char key, int x, int y) {
    if (key == 'd')
        move_right = true;
    if (key == 'a')
        move_left = true;
}

GameManager::~GameManager() { 
    if (main_shader)
        delete main_shader;
    if (light)
        delete light;
    if (world)
        delete world;
    if (casted_shadows)
        delete casted_shadows;
}

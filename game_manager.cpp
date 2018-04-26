#include "game_manager.h"

void GameManager::display(void) {
    light->fill_frame_buffer(*world);
    
    glViewport(0,0, screen_width, screen_height);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    light->draw_light(OpenGLContext::render_width, OpenGLContext::render_height);
    world->render_with_shader();
}

void GameManager::mouse_move(int x, int y) {
    light->light_x = (float)x;
    light->light_y = (float)y;
}

void GameManager::init_after_opengl_context() {
    shad = new ShaderProgram("shaders/main.vert", "shaders/main.frag");
    light = new Light();
    world = new World();
}


GameManager::~GameManager() { 
    if (shad)
        delete shad;
    if (light)
        delete light;
    if (world)
        delete world;
}

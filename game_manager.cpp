#include "game_manager.h"

GameManager::GameManager() : 
        main_shader("shaders/main.vert", "shaders/main.frag"),
        casted_shadows(OpenGLContext::render_width,
                       OpenGLContext::render_height),
        light(), world(), player() {}

void GameManager::display(void) {
    light.cast_shadows(world, OpenGLContext::render_width, OpenGLContext::render_height, casted_shadows);

    casted_shadows.copy_to(0);
    
    main_shader.use();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    world.draw();
    
    player.move(move_right - move_left, jump);
    player.draw();
}

void GameManager::mouse_move(int x, int y) {
    light.light_x = (float)x;
    light.light_y = (float)y;
}

void GameManager::key_up(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    if (key == 'd')
        move_right = false;
    if (key == 'a')
        move_left = false;
    if (key == ' ')
        jump = false;
        
}

void GameManager::key_down(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    if (key == 'd')
        move_right = true;
    if (key == 'a')
        move_left = true;
    if (key == ' ')
        jump = true;
}

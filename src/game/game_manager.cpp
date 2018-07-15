#include "game_manager.h"
#include <ctime>
#include <chrono>

double get_current_time_secs() {
    std::chrono::duration<double, std::milli>  ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    
    return ms.count()/1000;
}

GameManager::GameManager() : 
        main_shader("shaders/main.vert", "shaders/main.frag"),
        casted_shadows(OpenGLContext::screen->get_width(),
                       OpenGLContext::screen->get_height()),
        light(), world(), player(),
        keys(256, false) {}

        
void GameManager::display(void) {
    light.cast_shadows(world, casted_shadows);

    casted_shadows.copy_to(*OpenGLContext::screen);
    
    main_shader.use();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    world.draw();
    
    player.draw();
    
    double current_time = get_current_time_secs();
    double difference = current_time - last_update_time;
    
    // In the case of a large lag spike
    if (difference > .25) {
        last_update_time = get_current_time_secs();
        difference = 0;
    }
    
    player.move(keys['d'] - keys['a'], keys['s'] - keys['w'], keys[' '], difference);
    player.collide(casted_shadows);
    last_update_time = get_current_time_secs();
    
}

void GameManager::mouse_move(int x, int y) {
    light.light_x = (float)x;
    light.light_y = (float)y;
}

void GameManager::key_up(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    keys[key] = false;
}

void GameManager::key_down(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    keys[key] = true;
}

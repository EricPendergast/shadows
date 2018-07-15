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
    OpenGLContext::screen->bind();
    
    world.draw();
    
    player.draw();
    
    double current_time = get_current_time_secs();
    double difference = current_time - last_update_time;
    
    // In the case of a large lag spike
    if (difference > .25) {
        last_update_time = get_current_time_secs();
        difference = 0;
    }
    
    
    casted_shadows.copy_to(player.pixels_around_player,
            (int)player.x, 500-50-(int)player.y, 50, 50,
            0, 0, 256, 256);
    
    player.pixels_around_player.copy_to(*OpenGLContext::screen);
    
    player.move(keys['d'] - keys['a'], keys['s'] - keys['w'], keys[' '], difference);
    player.collide();
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

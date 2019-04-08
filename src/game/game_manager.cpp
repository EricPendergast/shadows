#include "game_manager.h"
#include <ctime>
#include <chrono>
#include <iostream>


double get_current_time_secs() {
    std::chrono::duration<double, std::milli>  ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    
    return ms.count()/1000;
}

GameManager::GameManager() : 
        keys(256, false) {}

        
void GameManager::display(void) {
    double current_time = get_current_time_secs();
    double difference = current_time - last_update_time;
    last_update_time = current_time;
    
    // In the case of a large lag spike
    if (difference > .1) {
        last_update_time = get_current_time_secs();
        difference = .1;
    }
    
    level.update(difference, keys['d'] - keys['a'], keys[' ']);

    level.render(OpenGLContext::screen);
}

void GameManager::mouse_move(int x, int y) {
    level.light.light_x = (float)x;
    level.light.light_y = (float)y;
}

void GameManager::key_up(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    keys[key] = false;
}

void GameManager::key_down(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    keys[key] = true;
}

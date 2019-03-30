#include "game_manager.h"
#include <ctime>
#include <chrono>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>



double get_current_time_secs() {
    std::chrono::duration<double, std::milli>  ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    
    return ms.count()/1000;
}

GameManager::GameManager() : 
        main_shader("shaders/main.vert", "shaders/main.frag"),
        collision_map(OpenGLContext::screen->get_width(),
                      OpenGLContext::screen->get_height()),
        light(), world(), player(), drawer(),
        keys(256, false) {}

        
void GameManager::display(void) {
    double current_time = get_current_time_secs();
    double difference = current_time - last_update_time;
    last_update_time = current_time;
    
    // In the case of a large lag spike
    if (difference > .25) {
        last_update_time = get_current_time_secs();
        difference = .1;
    }
    
    light.cast_shadows(world, collision_map.get_frame_buffer());
    
    //player.move(keys['d'] - keys['a'], keys[' '], difference);
    //
    //collision_map.copy_surrounding_pixels_to((int)player.x, (int)player.y, player.width, player.height, &player.pixels);
    //
    //player.collide();
    
    collision_map.get_frame_buffer().copy_to(*OpenGLContext::screen);
    
    main_shader.use();
    glUniformMatrix4fv(main_shader.get_uniform("world_to_screen"),
        1, GL_FALSE,
        glm::value_ptr(World::get_world_to_screen(
            0,
            0,
            (float)500,
            (float)500)));

    std::cout << OpenGLContext::screen->get_width() << std::endl;
    OpenGLContext::screen->bind();
    
    world.draw();
    
    //player.draw(&drawer);
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

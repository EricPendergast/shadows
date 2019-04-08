#include "level.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Level::Level() :
        main_shader("shaders/main.vert", "shaders/main.frag"),
        collision_map(OpenGLContext::screen->get_width(),
                      OpenGLContext::screen->get_height()),
        light(), world(), player() {}

void Level::update(double timestep, int player_lr, bool player_jump) {
    light.cast_shadows(world, collision_map.get_frame_buffer());
    
    player.move(player_lr, player_jump, timestep);
    
    collision_map.copy_surrounding_pixels_to((int)player.x, (int)player.y, player.width, player.height, &player.pixels);
    
    player.collide();
    
    collision_map.get_frame_buffer().copy_to(*OpenGLContext::screen);
}

void Level::render(FrameBuffer* render_to) {
    glm::mat4 world_to_screen = World::get_world_to_screen(
            0,
            0,
            (float)render_to->get_width(),
            (float)render_to->get_height());

    main_shader.use();
    main_shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(world_to_screen));

    world.draw();
    
    player.draw();

}

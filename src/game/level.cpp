#include "level.h"
#include "raii.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Level::Level() :
        main_shader("shaders/main.vert", "shaders/main.frag"),
        collision_map(
                new BasicBuffer(
                    OpenGLContext::screen->get_width(),
                    OpenGLContext::screen->get_height()),
                    0, 0),
        light(), world(), player() {}

void Level::update(double timestep, int player_lr, bool player_jump) {
    light.cast_shadows(world, collision_map);
    
    player.move(player_lr, player_jump, timestep);
    
    collision_map.copy_to(&player.pixels);

    player.collide();
}

void Level::render(FrameBuffer* render_to) {
    static float a = 0;

    collision_map.get_frame_buffer().copy_to(*render_to);

    WorldFramebuffer wfb(render_to, 
            a,
            0,
            (float)render_to->get_width(),
            (float)render_to->get_height());

    main_shader.use();
    main_shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(wfb.world_to_screen()));

    world.draw();
    
    player.draw();
}

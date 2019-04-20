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

float Level::a = 0;

void Level::render(FrameBuffer* render_to) {
    a += .1f;

    WorldFramebuffer screen(render_to, 
            a,
            -a,
            (float)render_to->get_width(),
            (float)render_to->get_height());

    collision_map.copy_to(&screen);

    main_shader.use();
    auto world_to_screen = screen.world_to_screen();
    main_shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(world_to_screen));

    world.draw();
    
    player.draw();
}

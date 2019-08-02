#include "level.h"
#include "raii.h"
#include "light_set.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>

Level::Level() :
        main_shader("shaders/main.vert", "shaders/main.frag"),
        world(), player(),
        objs() {

    objs.registerObj(std::make_shared<LightSet>());
}

void Level::update(double timestep, int player_lr, bool player_jump) {
    ControlInputs controls {
        .direction_lr = player_lr,
        .jump = player_jump
    };

    player.control(controls);

    for (auto& shadowCastable : objs.shadowCastableObjs) {
        shadowCastable->generate_shadows([this] {world.draw();});
    }

    auto drawColliders = [&] (WorldFrameBuffer& wfb) {
        for (auto& pixelCollidable : objs.pixelCollidableObjs) {
            pixelCollidable->render_pixel_collider(wfb);
        }
    };

    player.update(timestep, drawColliders);

    update_viewport();
}

float Level::a = 0;

void Level::render() {
    a += .1f;

    for (auto& renderable : objs.renderableObjs) {
        renderable->render(render_to);
    }

    main_shader.use();

    auto world_to_screen = render_to.world_to_screen();
    main_shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(world_to_screen));

    world.draw();
    
    player.render(render_to);
}

void Level::set_render_target(FrameBuffer* fb) {
    render_to = WorldFrameBuffer(fb, 0, 0);
}

// TODO: Add viewport following to the interface
void Level::update_viewport() {
    render_to = WorldFrameBuffer(render_to.frame_buffer, (float)player.x-400, (float)player.y-400);
}

void Level::on_mouse_press(float ndc_x, float ndc_y) {
    auto world_pos = glm::inverse(render_to.world_to_screen()) *
        glm::vec4(ndc_x, ndc_y, 0, 1);
    //light1.light_x = world_pos.x;
    //light1.light_y = world_pos.y;
}

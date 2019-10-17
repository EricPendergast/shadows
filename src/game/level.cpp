#include "level.h"
#include "raii.h"
#include "light_set.h"
#include "world.h"
#include "button.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>

Level::Level() :
        main_shader("shaders/main.vert", "shaders/main.frag"),
        objs() {

    objs.registerObj(std::make_shared<LightSet>());
    objs.registerObj(player = std::make_shared<Player>());
    objs.registerObj(std::make_shared<World>());
    objs.registerObj(std::make_shared<Button>(0, -250));
}

void Level::update(double timestep, int player_lr, bool player_jump) {
    ControlInputs controls {
        .direction_lr = player_lr,
        .jump = player_jump
    };

    for (auto& userControllable : objs.userControllableObjs) {
        userControllable->control(controls);
    }

    auto draw_opaque = [this] {
        for (auto& opaque : objs.opaqueObjs) {
            opaque->draw_opaque_shape();
        }
    };

    for (auto& shadowCastable : objs.shadowCastableObjs) {
        shadowCastable->generate_shadows(draw_opaque);
    }

    auto drawColliders = [&] (WorldFrameBuffer& wfb) {
        for (auto& pixelCollidable : objs.pixelCollidableObjs) {
            pixelCollidable->render_pixel_collider(wfb);
        }
    };

    for (auto& interactable : objs.interactableObjs) {
        for (auto& interactor : objs.interactorObjs) {
            if (interactor->can_interact(*interactable)) {
                interactable->do_action(*interactor);
            }
        }
    }

    for (auto& physical : objs.physicalObjs) {
        physical->update(timestep, drawColliders);
    }

    update_viewport();
}

void Level::render() {
    for (auto& renderable : objs.renderableObjs) {
        renderable->render(render_to);
    }
}

void Level::set_render_target(FrameBuffer* fb) {
    render_to = WorldFrameBuffer(fb, 0, 0);
}

// TODO: Add viewport following to the interface
void Level::update_viewport() {
    render_to = WorldFrameBuffer(render_to.frame_buffer, (float)player->x-400, (float)player->y-400);
}

// TODO: Modify the ControlInputs struct somehow
void Level::on_mouse_press(float ndc_x, float ndc_y) {
    auto world_pos = glm::inverse(render_to.world_to_screen()) *
        glm::vec4(ndc_x, ndc_y, 0, 1);
    //light1.light_x = world_pos.x;
    //light1.light_y = world_pos.y;
}

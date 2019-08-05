#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "world.h"

World::World() : vbo({
        450, -300, 0, 1,
        400, -300, 0, 1,
        400, -350, 0, 1,
        450, -350, 0, 1,
        0,   -500, 0, 1,
        400, -500, 0, 1,
        -500, -600, 0, 1,
        500, -600, 0, 1,
        500, -610, 0, 1,
    }),
    shader("shaders/main.vert", "shaders/main.frag") {}

void World::draw_opaque_shape() {
    vbo.draw();
}

void World::render(WorldFrameBuffer& render_to) {
    shader.use();
    auto world_to_screen = render_to.world_to_screen();
    shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(world_to_screen));
    vbo.draw();
}

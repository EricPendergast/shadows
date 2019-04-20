#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "world.h"

World::World() : vbo({
        450, 300, 0, 1,
        400, 300, 0, 1,
        400, 350, 0, 1,
        450, 350, 0, 1,
        0,   500, 0, 1,
        400, 500, 0, 1,
        400, 490, 0, 1,
        0,   490, 0, 1 }) {
}

void World::draw() {
    vbo.draw();
}

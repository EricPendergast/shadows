#ifndef SRC_GAME_WORLD_H
#define SRC_GAME_WORLD_H

#include "vbo.h"
#include "game_object_interfaces.h"
#include "shader.h"

#include <glm/detail/type_mat.hpp>

// This class is in charge of managing the position of blocks or various
// objects in the background of the world.
class World : public Renderable, public Opaque {
public:
    World();
    void draw_opaque_shape() override;
    void render(WorldFrameBuffer& render_to) override;
private:
    VBO vbo;
    ShaderProgram shader;
};

#endif

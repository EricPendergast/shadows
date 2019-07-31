#ifndef SRC_RENDERING_LIGHT_H
#define SRC_RENDERING_LIGHT_H

#include "depth_box_buffer.h"
#include "shader.h"
#include "world.h"
#include "vbo.h"
#include "world_frame_buffer.h"

class Light {
    // TODO: Platform independence. Is this the max framebuffer width for every
    // computer?
    int resolution = 8192;
    DepthBoxBuffer projection;
    ShaderProgram background_shader;
    VBO simple_box;

public:
    float light_x = 50, light_y = 50;
    Light(void);
    void render(WorldFrameBuffer& draw_to);
    void generate_shadows(std::function<void()> drawOpaqueShapes);
};

#endif

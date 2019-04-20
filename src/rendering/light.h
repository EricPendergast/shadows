#ifndef SRC_RENDERING_LIGHT_H
#define SRC_RENDERING_LIGHT_H

#include "depth_box_buffer.h"
#include "shader.h"
#include "world.h"
#include "vbo.h"
#include "collision_map.h"

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
    void cast_shadows(World& world, WorldFramebuffer& draw_to);
    
private:
    void fill_projection_buffer(World& world);
};

#endif

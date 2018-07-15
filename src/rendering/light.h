#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "depth_box_buffer.h"
#include "shader.h"
#include "printer.h"
#include "world.h"

#pragma once

class Light {
    // TODO: Platform independence. Is this the max framebuffer width for every
    // computer?
    int resolution = 8192;
    DepthBoxBuffer projection;
    ShaderProgram background_shader;

public:
    float light_x = 500, light_y = 500;
    Light(void);
    void cast_shadows(World& world, FrameBuffer& drawto);
    
private:
    void fill_projection_buffer(World& world);
};

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>

#include "raii.h"
#include "light.h"
#include "opengl_context.h"
#include "poly.h"

Light::Light(void): 
    projection(resolution),
    background_shader("shaders/shadow_background_box.vert", "shaders/shadow_background_box.frag"),
    simple_box(make_rect(0,0, 800, 800)) {}

void Light::generate_shadows(std::function<void()> drawOpaqueShapes) {
    WithBindFramebuffer w(&projection);
    projection.clear();
    projection.shader()->use();
    
    glUniform2f(projection.shader()->get_uniform("light_pos"), light_x, light_y);
    
    // Projecting onto each side of the box
    for (int i = 0; i < 4; i++)
        projection.draw(i, drawOpaqueShapes);
}

void Light::render(WorldFrameBuffer& draw_to) {
    glBindTexture(GL_TEXTURE_2D, projection.get_tex_handle());
    
    background_shader.use();
    glUniform2f(background_shader.get_uniform("light_pos"), light_x, light_y);
    
    auto world_to_screen = draw_to.world_to_screen();
    background_shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(world_to_screen));
    
    WithBindFramebuffer b(draw_to.frame_buffer);
    
    WithViewport w(0, 0, draw_to.frame_buffer->get_width(), draw_to.frame_buffer->get_height());
    simple_box.sub_data(0, make_rect(draw_to.x, draw_to.y, draw_to.width, draw_to.height));
    simple_box.draw();
}

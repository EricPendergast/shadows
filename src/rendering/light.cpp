#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include "raii.h"
#include "light.h"
#include "opengl_context.h"

using namespace std;

Light::Light(void): 
    projection(resolution),
    background_shader("shaders/shadow_background_box.vert", "shaders/shadow_background_box.frag"),
    simple_box({
        0, 0, 0, 1,
        800, 0, 0, 1,
        0, 800, 0, 1,
        0, 800, 0, 1,
        800, 800, 0, 1,
        800, 0, 0, 1}) {
    }

void Light::fill_projection_buffer(World& world) {
    projection.bind();
    projection.clear();
    projection.shader()->use();
    
    glUniform2f(projection.shader()->get_uniform("light_pos"), light_x, light_y);
    
    // Projecting onto each side of the box
    for (int i = 0; i < 4; i++)
        projection.draw(i, [&] {world.draw();});
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void Light::cast_shadows(World& world, FrameBuffer& draw_to) {
    fill_projection_buffer(world);
    
    glBindTexture(GL_TEXTURE_2D, projection.get_tex_handle());
    
    background_shader.use();
    glUniform2f(background_shader.get_uniform("light_pos"), light_x, light_y);
    
    auto world_to_screen = World::get_world_to_screen(
            0,
            0,
            (float)draw_to.get_width(),
            (float)draw_to.get_height());
    background_shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(world_to_screen));
    
    draw_to.bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    WithViewport w(0, 0, draw_to.get_width(), draw_to.get_height());
    simple_box.draw();
}

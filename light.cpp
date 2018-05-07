#include "light.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

using namespace std;

Light::Light(void): projection(resolution), background_shader("shaders/shadow_background_box.vert", "shaders/shadow_background_box.frag") {}

// TODO: Fix function name. Which frame buffer? Why are we filling it?
void Light::fill_frame_buffer(World& world) {
    projection.bind();
    projection.clear();
    projection.shader()->use();
    
    glUniform2f(projection.shader()->get_uniform("light_pos"), light_x, light_y);
    
    for (int i = 0; i < 4; i++) {
        // Drawing to row i
        projection.begin_draw(i);
        world.draw();
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}


void Light::draw_light(int screen_width, int screen_height) {
    glViewport(0,0, screen_width, screen_height);
    
    glBindTexture(GL_TEXTURE_2D, projection.get_tex_handle());
    
    background_shader.use();
    glUniform2f(background_shader.get_uniform("light_pos"), light_x, light_y);
    
    glm::mat4 transform = glm::scale(glm::vec3(2.0f/(float)screen_width, -2.0f/(float)screen_height, 1.0f));
    transform = glm::translate(glm::vec3(-1,1,0)) * transform;

    glUniformMatrix4fv(background_shader.get_uniform("mat"), 1, GL_FALSE, glm::value_ptr(transform));
    
    // Binding the deafult frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f((GLfloat)screen_width,0);
    glVertex2f((GLfloat)screen_width,(GLfloat)screen_height);
    glVertex2f(0,(GLfloat)screen_height);
    glEnd();
}


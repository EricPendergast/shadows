#include "light.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

using namespace std;

Light::Light(void): projection(resolution), light_shader("shaders/light_box.vert", "shaders/light_box.frag"), background_shader("shaders/shadow_background_box.vert", "shaders/shadow_background_box.frag") {}

void Light::fill_frame_buffer(World& world) {
    glEnable(GL_DEPTH_TEST);
    // 
    glBindTexture(GL_TEXTURE_2D, projection.get_tex_handle());
    glBindFramebuffer(GL_FRAMEBUFFER, projection.get_fbo_handle());
    

    glClearColor(10000000, 10000000, 10000000, 1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    // TODO: Translate with x and y
    //glTranslatef(0, 0, 0);
    light_shader.use();
    glUniform2f(light_shader.get_uniform("light_pos"), light_x, light_y);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-light_x, -light_y, 0));
    
    glUniformMatrix4fv(light_shader.get_uniform("proj"), 1, GL_FALSE, glm::value_ptr(translate));
    
    //glViewport(0,0, projection.width, 2);
    //glUniform1f(light_shader.get_uniform("horiz_or_vert"), -1);
    //world.draw();
    glViewport(0,2, projection.width, 2);
    glUniform1f(light_shader.get_uniform("horiz_or_vert"), 1);
    world.draw();
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}


void Light::draw_light(int screen_width, int screen_height) {
    glViewport(0,0, screen_width, screen_height);
    
    glBindTexture(GL_TEXTURE_2D, projection.get_tex_handle());
    // For debugging
    float data[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    glTexSubImage2D(GL_TEXTURE_2D, 0, /*x*/0,/*y*/0, /*width*/20, /*height*/1, GL_RGBA32F, GL_FLOAT, data);
    
    
    background_shader.use();
    
    glm::mat4 transform = glm::scale(glm::vec3(2.0f/(float)screen_width, 2.0f/(float)screen_height, 1.0f));
    transform = glm::translate(glm::vec3(-1,-1,0)) * transform;

    glUniformMatrix4fv(background_shader.get_uniform("mat"), 1, GL_FALSE, glm::value_ptr(transform));
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f((GLfloat)screen_width,0);
    glVertex2f((GLfloat)screen_width,(GLfloat)screen_height);
    glVertex2f(0,(GLfloat)screen_height);
    glEnd();
    
}


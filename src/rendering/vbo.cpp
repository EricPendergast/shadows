#include "vbo.h"
#include <iostream>

VBO::VBO(const std::vector<GLfloat>& verticies) {
    GLenum error = glGetError();

    glGenVertexArrays(1, &vao_handle);
    glGenBuffers(1, &vbo_handle);

    bind();

    glBufferData(GL_ARRAY_BUFFER, verticies.size()*sizeof(GLfloat), &verticies[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "ERROR: Could not create a VBO: %s \n" 
                << gluErrorString(error) << std::endl;
        exit(-1);
    }

    unbind();
}

VBO::~VBO() {
    GLenum error = glGetError();

    //glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo_handle);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao_handle);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "ERROR: Could not destroy the VBO: %s \n"
            << gluErrorString(error) << std::endl;
        exit(-1);
    }
}

void VBO::draw() {
    bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    unbind();
}

void VBO::bind() {
    glBindVertexArray(vao_handle);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);
    glEnableVertexAttribArray(0);
}

void VBO::unbind() {
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

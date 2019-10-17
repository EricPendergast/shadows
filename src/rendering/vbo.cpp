#include "vbo.h"

#include <iostream>
#include <assert.h>

VBO::VBO(const std::vector<GLfloat>& verticies) : num_verts(verticies.size()/4){
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
    glDrawArrays(GL_TRIANGLES, 0, (int)num_verts);
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

void VBO::sub_data(size_t offset_bytes, size_t num_bytes, const char* bytes) {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset_bytes, num_bytes, bytes);
    unbind();
}

VBO VBO::from_quads(const std::vector<GLfloat>& quads) {
    assert(quads.size() % (4*4) == 0);
    std::vector<GLfloat> verts;
    for (int i = 0; i < quads.size(); i += 4) {
        verts.insert(verts.end(), quads.begin() + (i+0)*4, quads.begin() + (i+3)*4);
        verts.insert(verts.end(), quads.begin() + (i+2)*4, quads.begin() + (i+4)*4);
        verts.insert(verts.end(), quads.begin() + (i+0)*4, quads.begin() + (i+1)*4);
    }

    return VBO(verts);
}

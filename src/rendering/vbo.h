#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

class VBO {
    GLuint vao_handle;
    GLuint vbo_handle;
    void bind();
    void unbind();
public:
    VBO(const std::vector<GLfloat>& verticies);
    ~VBO();
    void draw();
};

#ifndef SRC_RENDERING_VBO_H
#define SRC_RENDERING_VBO_H


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
    template <typename T>
    void sub_data(size_t offset, const std::vector<T>& vec) {
        if (!vec.empty())
            sub_data(offset*sizeof(T), vec.size()*sizeof(T), (char*)(&vec[0]));
    }

    void sub_data(size_t offset_bytes, size_t num_bytes, const char* bytes);
};

#endif

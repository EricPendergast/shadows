#include <GL/glew.h>
#include <string>

#ifndef SHADER_H
#define SHADER_H

typedef std::string Filename;

class ShaderProgram {
private:
    GLuint program;
public:
    ShaderProgram(Filename vert_filename, Filename frag_filename);
    GLuint get_handle();
    GLint get_uniform(std::string name);
    GLint get_uniform(const char* name);
    void set_uniform_Matrix4f(std::string name, const float* matrix);
    void use();
};
#endif

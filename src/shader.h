#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <assert.h>

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
    void use();
};
#endif

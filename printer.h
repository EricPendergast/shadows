#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <iostream>
#include <sstream>

#ifndef PRINTER_H
#define PRINTER_H
std::string getRenderbufferParameters(GLuint id);
std::string getTextureParameters(GLuint id);
std::string convertInternalFormatToString(GLenum format);
void printFramebufferInfo(GLuint fbo);
    

#endif

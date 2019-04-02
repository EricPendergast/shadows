#include "shader.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

void print_program_info_log(GLuint obj);
void load_compile_shader(GLuint handle, std::string filename);
void print_shader_info_log(GLuint obj);
    
ShaderProgram::ShaderProgram(std::string vert_filename, std::string frag_filename) {
    program = glCreateProgram();
    
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    load_compile_shader(vertShader, vert_filename);
    load_compile_shader(fragShader, frag_filename);
    
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    
    glLinkProgram(program);
    
    // Error checking
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        
     

        glDeleteProgram(program);

        exit(1);
    }
    
    print_program_info_log(program);
    print_shader_info_log(vertShader);
    print_shader_info_log(fragShader);
}

void ShaderProgram::use() {
    glUseProgram(get_handle());
}
GLuint ShaderProgram::get_handle() {
    return program;
}

GLint ShaderProgram::get_uniform(const char* name) {
    GLint loc = glGetUniformLocation(program, name);
    // This is commented because it is often very annoying since unused
    // uniforms are optimized out of shaders.
    //if (loc == -1) {
    //    std::cerr << "Invalid uniform \"" << name << "\"" << std::endl;
    //    exit(1);
    //}
    return loc;
}

GLint ShaderProgram::get_uniform(std::string name) {
    return get_uniform(name.c_str());
}

void load_compile_shader(GLuint handle, std::string filename) {
    std::ifstream t(filename.c_str());
    std::string sc((std::istreambuf_iterator<char>(t)),
    std::istreambuf_iterator<char>());
    
    //Send the vertex shader source code to GL
    const GLchar *source = (const GLchar *)sc.c_str();
    glShaderSource(handle, 1, &source, 0);

    //Compile the vertex shader
    glCompileShader(handle);

    GLint isCompiled = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(handle, maxLength, &maxLength, &infoLog[0]);

        std::cout << "Shader " << filename << " did not compile." << std::endl;
        for (GLchar c : infoLog)
            std::cout << c;
        //TODO: can use infolog
        exit(1);
    }
}


void print_program_info_log(GLuint obj) {
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0) {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

void ShaderProgram::set_uniform_Matrix4f(std::string name, const float* matrix) {
    glUniformMatrix4fv(this->get_uniform(name),
        1, GL_FALSE,
        matrix);
}

void print_shader_info_log(GLuint obj) {
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0) {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

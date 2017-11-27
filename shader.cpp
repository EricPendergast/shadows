#include "shader.h"

void load_compile_shader(GLuint handle, std::string filename);
    
ShaderProgram::ShaderProgram(Filename vert_filename, Filename frag_filename) {
    program = glCreateProgram();
    
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    //GLuint fragShader = glCreateShader(GL_VERTEX_SHADER);
    
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
}

GLuint ShaderProgram::get_handle() {
    return program;
}

void load_compile_shader(GLuint handle, std::string filename) {
    std::ifstream t(filename.c_str());
    std::string sc((std::istreambuf_iterator<char>(t)),
    std::istreambuf_iterator<char>());
    
    //Send the vertex shader source code to GL
    //Note that std::string's .c_str is NULL character terminated.
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
        //TODO: can use infolog
        exit(1);
    }
}

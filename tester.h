#ifndef TESTER_H
#define TESTER_H

#include "opengl_context.h"
#include "shader.h"
#include <assert.h>

class Tester: public OpenGLContext::GameManagerInterface { 
    bool ran_once = false;
    
    virtual void display();
    void run_tests();
};

#endif

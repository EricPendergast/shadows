#ifndef TESTER_H
#define TESTER_H

#include <assert.h>
#include <cmath>

#include "opengl_context.h"
#include "shader.h"

// This class "pretends" to be a game engine, but just runs all the tests
// during the first loop, and then exits.
class Tester: public OpenGLContext::GameManagerInterface { 
    bool ran_once = false;
    
    virtual void display();
    void run_tests();
    ~Tester();
};

#endif

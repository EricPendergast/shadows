#ifndef TESTER_H
#define TESTER_H

#include <assert.h>
#include <cmath>

#include "opengl_context.h"
#include "shader.h"
#include "basic_buffer.h"
#include "depth_box_buffer.h"
#include "compressor.h"

// This class "pretends" to be a game engine, but just runs all the tests
// during the first loop, and then exits.
class Tester: public OpenGLContext::GameManagerInterface { 
    bool ran_once = false;
    
    virtual void display();
    void run_tests();
    ~Tester();
};

#endif

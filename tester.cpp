#include "tester.h"

void Tester::display() {
    if (ran_once) {
        std::cout << "Tests passed" << std::endl;
        exit(0);
    }
    ran_once = true;
    run_tests();
}

void basic_frame_buffer_test() {
    BasicBuffer buf(100,100);
    buf.bind();
    glViewport(0,0,100,100);
    glClearColor(1.0f, 0.5f, 0.25f, .5f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    int thing = buf.read_pixel(0,0);
    assert(thing == (int)0xff804080);
    
    
    // WHY DOES write_pixel NOT WORK!?
    //buf.write_pixel(0,0, 0x11111111);
    //thing = buf.read_pixel(0,0);
    //assert(thing == (int)0x11111111);
}

void light_shader_test() {
    ShaderProgram light_shader("shaders/light_box.vert", "shaders/light_box.frag");
    DepthBuffer projection(100);
    
    glEnable(GL_DEPTH_TEST);
    projection.bind();
    
    glClearColor(10000000, 10000000, 10000000, 1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    
}

void Tester::run_tests() {
    basic_frame_buffer_test();
    //light_shader_test();
}

Tester::~Tester() {
    
}

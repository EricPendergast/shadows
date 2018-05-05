#include "tester.h"

void Tester::display() {
    if (ran_once) {
        std::cout << "Tests passed" << std::endl;
        exit(0);
    }
    ran_once = true;
    run_tests();
}



bool equal(std::vector<float> a, std::vector<float> b) {
    float epsilon = .00001f;
    if (a.size() != b.size())
        return false;
    
    for (unsigned int i = 0; i < a.size(); i++)
        if (std::abs(a[i]-b[i]) > epsilon)
            return false;
    
    return true;
}

void print(std::vector<float> v) {
    std::cout << "[";
    for (auto t : v)
        std::cout << t << " ";
    std::cout << "]" << std::endl;
}

// These tests are here not only as tests, but also as notes for how these
// things should be used.


void basic_frame_buffer_test() {
    BasicBuffer buf(100,100);
    buf.bind();
    glViewport(0,0,100,100);
    glClearColor(1.0f, 0.5f, 0.25f, .5f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //int thing = buf.read_pixel(0,0);
    //assert(thing == (int)0xff804080);
    assert(equal(buf.read_pixel(0,0), {1.0f, 0.5f, 0.25f, .5f}));
    
    
    
    // WHY DOES write_pixel NOT WORK!?
    //buf.write_pixel(0,0, 0x11111111);
    //thing = buf.read_pixel(0,0);
    //assert(thing == (int)0x11111111);
}

void light_shader_test() {
    DepthBoxBuffer projection(100);
    
    projection.bind();
    projection.clear();
    // We are rendering to the top of the box
    projection.begin_draw(DepthBoxBuffer::UP);
    
    glUniform2f(projection.shader()->get_uniform("light_pos"), 0, 0);
    
    print(projection.read_pixel(50, DepthBoxBuffer::UP));
            
    // Tests default depth
    assert(equal(projection.read_pixel(0, DepthBoxBuffer::UP), DepthBoxBuffer::DEFAULT_DEPTH));
    
    // For now, shader pretends we are always projecting to the top row.
    glBegin(GL_QUADS);
    glVertex2f(-1,2);
    glVertex2f(1,2);
    glVertex2f(1,3);
    glVertex2f(-1,3);
    glEnd();
    
    // Tests depth interpolation
    assert(equal(projection.read_pixel(50, DepthBoxBuffer::UP), {2,0,0,1}));
    
    
}

void Tester::run_tests() {
    basic_frame_buffer_test();
    light_shader_test();
}

Tester::~Tester() {
    
}

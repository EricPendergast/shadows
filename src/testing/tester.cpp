#include "tester.h"

void Tester::display() {
    if (ran_once) {
        std::cout << "Tests passed" << std::endl;
        exit(0);
    }
    ran_once = true;
    run_tests();
}



// Checks that the two vectors are componentwise equal within an epsilon
bool equal(std::vector<float> a, std::vector<float> b) {
    float epsilon = .1f;
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


void basic_frame_buffer_test() {
    BasicBuffer buf(100,100);
    buf.bind();
    WithViewport w(0,0,100,100);
    glClearColor(1.0f, 0.5f, 0.25f, .5f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    assert(equal(buf.read_pixel(0,0), {1.0f, 0.5f, 0.25f, .5f}));
    
    // write_pixel does not work right now.
     
    //buf.write_pixel(0,0, 0x11111111);
    //thing = buf.read_pixel(0,0);
    //assert(thing == (int)0x11111111);
}

void draw_square(float x, float y, float width) {
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+width,y);
    glVertex2f(x+width,y+width);
    glVertex2f(x,y+width);
    glEnd();
}

// Tests drawing a cube right in front of the camera.
void light_shader_test_1() {
    DepthBoxBuffer projection(100);
    
    projection.bind();
    
    projection.clear();
    // Rendering to the top of the box
    projection.draw(DepthBoxBuffer::UP, [&] {
        glUniform2f(projection.shader()->get_uniform("light_pos"), 0, 0);
        // Tests default depth
        assert(equal(projection.read_pixel(0, DepthBoxBuffer::UP),
                     DepthBoxBuffer::DEFAULT_DEPTH));
        draw_square(-1,10,1.25);
        // Tests depth interpolation
        assert(equal(projection.read_pixel(50, DepthBoxBuffer::UP),
                     {10,0,0,1}));
    });
    

    projection.clear();
    projection.draw(DepthBoxBuffer::UP, [&] {
        glUniform2f(projection.shader()->get_uniform("light_pos"), -.9f, 0);
        draw_square(-1,3,.5);
        assert(equal(projection.read_pixel(50, DepthBoxBuffer::UP),
                     {3,0,0,1}));
    });

    projection.clear();
    projection.draw(DepthBoxBuffer::UP, [&] {
        glUniform2f(projection.shader()->get_uniform("light_pos"), -1.1f, 0);
        draw_square(-1,3,.5);
        assert(equal(projection.read_pixel(50, DepthBoxBuffer::UP),
                     DepthBoxBuffer::DEFAULT_DEPTH));
    });

    projection.clear();
    // Drawing behind the camera
    projection.draw(DepthBoxBuffer::UP, [&] {
        glUniform2f(projection.shader()->get_uniform("light_pos"), 0, 0);
        draw_square(-1,-3,.5);
        for (int i = 0; i < 100; i++)
            assert(equal(projection.read_pixel(i, DepthBoxBuffer::UP),
                         DepthBoxBuffer::DEFAULT_DEPTH));
    });


    projection.clear();
    projection.draw(DepthBoxBuffer::DOWN, [&] {
        glUniform2f(projection.shader()->get_uniform("light_pos"), 0, 0);
        draw_square(0,-3,2);
        assert(!equal(projection.read_pixel(75, DepthBoxBuffer::DOWN),
                     DepthBoxBuffer::DEFAULT_DEPTH));
        assert(equal(projection.read_pixel(25, DepthBoxBuffer::DOWN),
                     DepthBoxBuffer::DEFAULT_DEPTH));
    });
    
    
    // This commented code is nice for debugging.
    //for (int i = 0; i < 4; i++) {
    //    for (int j = 0; j < 100; j++) {
    //        std::cout << projection.read_pixel(j, i)[0] << " ";
    //    }
    //    std::cout << std::endl;
    //}
    //std::cout << std::endl;
    
    // TODO: RIGHT and LEFT tests
}


// Tests proper clipping
void light_shader_test_2() {
    DepthBoxBuffer projection(100);
    projection.bind();
    
    projection.draw(DepthBoxBuffer::UP, [&] {
        glUniform2f(projection.shader()->get_uniform("light_pos"), 0, 0);
        draw_square(1,-20,40);
        assert(!equal(projection.read_pixel(99, DepthBoxBuffer::UP), DepthBoxBuffer::DEFAULT_DEPTH));
        assert(equal(projection.read_pixel(50, DepthBoxBuffer::UP), DepthBoxBuffer::DEFAULT_DEPTH));
        assert(equal(projection.read_pixel(0, DepthBoxBuffer::UP), DepthBoxBuffer::DEFAULT_DEPTH));
        draw_square(-41,-20,40);
        assert(equal(projection.read_pixel(50, DepthBoxBuffer::UP), DepthBoxBuffer::DEFAULT_DEPTH));
        assert(!equal(projection.read_pixel(0, DepthBoxBuffer::UP), DepthBoxBuffer::DEFAULT_DEPTH));
    });
    
    projection.write_to_tga_file("debug_output/basic.tga");
}


void compression_test_1() {
    BasicBuffer source(16,16);
    
    
    Compressor c(16,16, 1,1, ShaderProgram("basic_compression.vert", "basic_compression.frag"));
    
    c.compress(&source);
}

void Tester::run_tests() {
    basic_frame_buffer_test();
    light_shader_test_1();
    light_shader_test_2();
}

Tester::~Tester() {
    
}

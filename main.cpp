
#include <string>

#include "frame_buffer.h"
#include "game_manager.h"
#include "light.h"
#include "opengl_context.h"
#include "printer.h"
#include "shader.h"
#include "tester.h"
#include "world.h"

int main(int argc, char** argv) {
    if (argc >= 2 && std::string(argv[1]) == "run_tests") {
        OpenGLContext::manager = new Tester();
        argc--;
        argv++;
    } else {
        OpenGLContext::manager = new GameManager();
    }
    
    OpenGLContext::init_context(argc, argv);
    
    OpenGLContext::manager->init_after_opengl_context();
    
    OpenGLContext::start_running();
    
    
    delete OpenGLContext::manager;
    //glBindFramebuffer(GL_FRAMEBUFFER, fb.get_fbo_handle());
    //int pix;
    //glReadPixels(1,1, 1,1, GL_GREEN, GL_INT, &pix);
    //pix = 0x00FFFF00;
    //glRasterPos2i(48,56);
    //glDrawPixels(1,1, GL_RGB, GL_INT, &pix);
    //std::cout << "HERE " << std::hex << pix << std::endl;
    
    //printFramebufferInfo(fb.get_fbo_handle());
}

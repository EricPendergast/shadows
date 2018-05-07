#include <string>

#include "game_manager.h"
#include "opengl_context.h"
#include "tester.h"

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
}

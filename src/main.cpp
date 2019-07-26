#include <string>

#include "game_manager.h"
#include "opengl_context.h"
#include "tester.h"

int main(int argc, char** argv) {
    OpenGLContext::init_context(argc, argv);
    
    if (argc >= 2 && std::string(argv[1]) == "run_tests") {
        OpenGLContext::manager = std::make_unique<Tester>();
    } else {
        OpenGLContext::manager = std::make_unique<GameManager>();
    }
    
    OpenGLContext::start_running();
}

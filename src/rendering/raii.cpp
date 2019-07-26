#include "raii.h"
#include "opengl_context.h"

decltype(make_deques(functions)) global::gl_call_stacks = make_deques(functions);

void set_raii_defaults() {
    WithViewport::set_default(0,0,0,0);
    WithDepthTestEnabled::set_default(false);
    WithClearColor::set_default(1.f, 0.f, 0.f, 1.f);
    WithPolygonMode::set_default(GL_FRONT_AND_BACK, GL_FILL);
    WithBindFramebuffer::set_default(OpenGLContext::screen.get());
    WithScissorTestEnabled::set_default(false);
}

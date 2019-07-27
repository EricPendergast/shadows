#include <GL/glew.h>
#include "frame_buffer.h"

template<GLenum capability>
static void gl_set_enabled(bool enabled) {
    if (enabled) {
        glEnable(capability);
    } else {
        glDisable(capability);
    }
}

static void gl_bind_framebuffer(FrameBuffer* fb) {
    glBindFramebuffer(GL_FRAMEBUFFER, fb->get_fbo_handle());
}

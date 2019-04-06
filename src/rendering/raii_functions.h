#include <GL/glew.h>
#include "frame_buffer.h"

static void gl_set_depth_test_enabled(bool enabled) {
    if (enabled) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

static void gl_bind_framebuffer(FrameBuffer* fb) {
    glBindFramebuffer(GL_FRAMEBUFFER, fb->get_fbo_handle());
}

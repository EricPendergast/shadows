#ifndef SRC_RENDERING_FRAME_BUFFER_DEPTH_BOX_BUFFER_H
#define SRC_RENDERING_FRAME_BUFFER_DEPTH_BOX_BUFFER_H

#include <functional>

#include "frame_buffer.h"
#include "shader.h"


// Intended to be used as a shadow buffer which is a square around a
// point. Contains a frame buffer with given width and height 4. Uses a
// renderbuffer for depth testing, and writes depth values to its texture, to
// be read by a shader at a later point.
class DepthBoxBuffer : public FrameBuffer {
public:
    // These constants specify which row corresponds to each side of the
    // square.
    // Note: These are the same values as defined in light_box.vert
    static const int UP = 0;
    static const int DOWN = 1;
    static const int RIGHT = 2;
    static const int LEFT = 3;
    static const std::vector<float> DEFAULT_DEPTH;
    
    ShaderProgram projection_shader;
    
    DepthBoxBuffer(int width);
    // To be called before drawing. Enables the projection shader.
    void draw(int row, std::function<void()> draw);
    // Prepares depth and color buffers for rendering
    void clear();
    ShaderProgram* shader();
};

#endif

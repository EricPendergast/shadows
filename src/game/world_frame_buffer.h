#ifndef SRC_GAME_COLLISION_MAP_H
#define SRC_GAME_COLLISION_MAP_H

#include "frame_buffer.h"
#include "basic_buffer.h"
#include <glm/detail/type_mat.hpp>

// Represents a framebuffer which is tied to a position and size in world
// coordinates
class WorldFrameBuffer {
public:
    FrameBuffer* frame_buffer;
    // Returns a matrix mapping world coordinates to screen coordinates
    // (normalized device coordinates)
    glm::mat4 world_to_screen();
    // Map world coordinates to coordinates which refer to a pixel in
    // frame_buffer
    glm::mat4 world_to_pixel();
    WorldFrameBuffer();
    WorldFrameBuffer(FrameBuffer* frame_buffer, float x, float y, float w, float h);
    WorldFrameBuffer(FrameBuffer* frame_buffer, float x, float y);
    // Position of the upper left corner of the buffer in world coordinates
    float x, y;
    float width, height;

    // Takes world coordinates
    void copy_to(WorldFrameBuffer* output);
    FrameBuffer& get_frame_buffer();
};

#endif

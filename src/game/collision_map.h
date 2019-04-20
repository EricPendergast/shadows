#ifndef SRC_GAME_COLLISION_MAP_H
#define SRC_GAME_COLLISION_MAP_H

#include "frame_buffer.h"
#include "basic_buffer.h"

#include <memory>
#include <glm/detail/type_mat.hpp>

class CollisionMap {
public:
    CollisionMap(int width, int height);
    FrameBuffer& get_frame_buffer();
    // Takes inputs in physical coordinates
    void copy_surrounding_pixels_to(int x, int y, int w, int h, FrameBuffer* output);
private:
    BasicBuffer collision_map;
};

// Represents a framebuffer which is tied to a position and size in world
// coordinates
class WorldFramebuffer {
public:
    FrameBuffer* frame_buffer;
    // Returns a matrix mapping world coordinates to screen coordinates
    // (normalized device coordinates)
    glm::mat4 world_to_screen();
    // Map world coordinates to coordinates which refer to a pixel in
    // frame_buffer
    glm::mat4 world_to_pixel();
    WorldFramebuffer(FrameBuffer* frame_buffer, float x, float y, float w, float h);
    WorldFramebuffer(FrameBuffer* frame_buffer, float x, float y);
    // Position of the upper left corner of the buffer in world coordinates
    float x, y;
    float width, height;

    // Takes world coordinates
    void copy_to(WorldFramebuffer* output);
    FrameBuffer& get_frame_buffer();
};

#endif

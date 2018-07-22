#include "basic_buffer.h"

#pragma once

class CollisionMap {
public:
    CollisionMap(int width, int height);
    BasicBuffer& get_frame_buffer();
    // Takes inputs in physical coordinates
    void copy_surrounding_pixels_to(int x, int y, int w, int h, FrameBuffer* output);
private:
    BasicBuffer collision_map;
};

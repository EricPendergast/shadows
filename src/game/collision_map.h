#ifndef SRC_GAME_COLLISION_MAP_H
#define SRC_GAME_COLLISION_MAP_H

#include "basic_buffer.h"


class CollisionMap {
public:
    CollisionMap(int width, int height);
    BasicBuffer& get_frame_buffer();
    // Takes inputs in physical coordinates
    void copy_surrounding_pixels_to(int x, int y, int w, int h, FrameBuffer* output);
private:
    BasicBuffer collision_map;
};

#endif

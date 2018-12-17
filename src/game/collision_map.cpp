#include "collision_map.h"

CollisionMap::CollisionMap(int width, int height) : collision_map(width, height) {}

void CollisionMap::copy_surrounding_pixels_to(int x, int y, int w, int h, FrameBuffer* output) {
    collision_map.copy_to(*output,
            x-w, collision_map.get_height()-h-y-h, w*3, h*3,
            0, 0, output->get_width(), output->get_height());
    output->write_to_tga_file("debug_output/collide.tga");
}

BasicBuffer& CollisionMap::get_frame_buffer() {
    return collision_map;
}

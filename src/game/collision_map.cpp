#include "collision_map.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <algorithm>

CollisionMap::CollisionMap(int width, int height) : collision_map(width, height) {}

void CollisionMap::copy_surrounding_pixels_to(int x, int y, int w, int h, FrameBuffer* output) {
    collision_map.copy_to(*output,
            x-w, collision_map.get_height()-h-y-h, w*3, h*3,
            0, 0, output->get_width(), output->get_height());
    output->write_to_tga_file("debug_output/collide.tga");
}

FrameBuffer& CollisionMap::get_frame_buffer() {
    return collision_map;
}


WorldFramebuffer::WorldFramebuffer(FrameBuffer* frame_buffer, float x, float y, float w, float h) :
    frame_buffer(frame_buffer),
    x(x), y(y),
    width(w), height(h) {}

WorldFramebuffer::WorldFramebuffer(FrameBuffer* frame_buffer, float x, float y) :
    WorldFramebuffer(frame_buffer, x, y, (float)frame_buffer->get_width(), (float)frame_buffer->get_height()) {}

FrameBuffer& WorldFramebuffer::get_frame_buffer() {
    return *frame_buffer;
}

void WorldFramebuffer::copy_to(WorldFramebuffer* out) {
    // TODO: What if the width of this frame buffer in pixels differs from its
    // width in world coordinates?
    auto transform = world_to_pixel();
    auto lower_left_corner = transform * glm::vec4(out->x, out->y, 0, 1);
    auto upper_right_corner = transform * glm::vec4(out->x+out->width, out->y+out->height, 0, 1);
    int new_x = (int)lroundf(lower_left_corner.x);
    int new_y = (int)lroundf(lower_left_corner.y);
    int new_w = (int)lroundf(upper_right_corner.x - lower_left_corner.x);
    int new_h = (int)lroundf(upper_right_corner.y - lower_left_corner.y);

    new_x = std::min(new_x, new_x + new_w);
    new_y = std::min(new_y, new_y + new_h);
    new_w = abs(new_w);
    new_h = abs(new_h);

    frame_buffer->copy_to(*out->frame_buffer, new_x, new_y, new_w, new_h,
            0, 0, out->frame_buffer->get_width(), out->frame_buffer->get_height());
}

glm::mat4 WorldFramebuffer::world_to_screen() {
    assert(abs(width - (float)frame_buffer->get_width()) < .0001);
    assert(abs(height - (float)frame_buffer->get_height()) < .0001);
    auto transform = glm::translate(glm::vec3(x, y, 0));
    transform = glm::scale(glm::vec3(2.0f/width, -2.0f/height, 1.0f)) * transform;
    return glm::translate(glm::vec3(-1,1,0)) * transform;
}

glm::mat4 WorldFramebuffer::world_to_pixel() {
    assert(abs(width - (float)frame_buffer->get_width()) < .0001);
    assert(abs(height - (float)frame_buffer->get_height()) < .0001);
    auto transform = glm::translate(glm::vec3(0, height, 0)) * glm::scale(glm::vec3(1, -1, 1));
    return transform;
}

#include "world_frame_buffer.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <algorithm>

WorldFrameBuffer::WorldFrameBuffer() : frame_buffer(nullptr), x(0), y(0), width(0), height(0) {}

WorldFrameBuffer::WorldFrameBuffer(FrameBuffer* frame_buffer, float x, float y, float w, float h) :
    frame_buffer(frame_buffer),
    x(x), y(y),
    width(w), height(h) {

    assert(frame_buffer != nullptr);
}

WorldFrameBuffer::WorldFrameBuffer(FrameBuffer* frame_buffer, float x, float y) :
    WorldFrameBuffer(frame_buffer, x, y, (float)frame_buffer->get_width(), (float)frame_buffer->get_height()) {
    
    assert(frame_buffer != nullptr);
}

FrameBuffer& WorldFrameBuffer::get_frame_buffer() {
    return *frame_buffer;
}

void WorldFrameBuffer::copy_to(WorldFrameBuffer* out) {
    // TODO: What if the width of this frame buffer in pixels differs from its
    // width in world coordinates?
    auto transform = world_to_pixel();
    // All that the logic requires here is that corner1 and corner2 are
    // diagonally opposite from each other
    auto corner1 = transform * glm::vec4(out->x, out->y, 0, 1);
    auto corner2 = transform * glm::vec4(out->x+out->width, out->y+out->height, 0, 1);
    int new_x = (int)lroundf(corner1.x);
    int new_y = (int)lroundf(corner1.y);
    int new_w = (int)lroundf(corner2.x - corner1.x);
    int new_h = (int)lroundf(corner2.y - corner1.y);

    new_x = std::min(new_x, new_x + new_w);
    new_y = std::min(new_y, new_y + new_h);
    new_w = abs(new_w);
    new_h = abs(new_h);

    frame_buffer->copy_to(*out->frame_buffer, new_x, new_y, new_w, new_h,
            0, 0, out->frame_buffer->get_width(), out->frame_buffer->get_height());
}

glm::mat4 WorldFrameBuffer::world_to_screen() {
    assert(abs(width - (float)frame_buffer->get_width()) < .0001);
    assert(abs(height - (float)frame_buffer->get_height()) < .0001);

    return glm::translate(glm::vec3(-1,1,0)) * glm::scale(glm::vec3(2.0f/width, -2.0f/height, 1.0f)) * glm::translate(glm::vec3(-x, -y, 0));
}

glm::mat4 WorldFrameBuffer::world_to_pixel() {
    assert(abs(width - (float)frame_buffer->get_width()) < .0001);
    assert(abs(height - (float)frame_buffer->get_height()) < .0001);

    return glm::translate(glm::vec3(0, height, 0)) * glm::scale(glm::vec3(1, -1, 1)) * glm::translate(glm::vec3(-x, -y, 0));
}

#include <math.h>
#include <glm/glm.hpp>

#include "gpu_collider.h"
#include "basic_buffer.h"

float round(float a, float inc) {
    return std::round(a/inc)*inc;
}

float floor(float a, float inc) {
    return std::floor(a/inc)*inc;
}

GPUCollider::GPUCollider(double collide_res_scale, double w, double h) :
    x(0), y(0),
    width(w), height(h),
    collide_res_scale(collide_res_scale),
    sum_squares((int)(w*collide_res_scale)*4, (int)(h*collide_res_scale)*4),
    pixels(new BasicBuffer((int)(w*collide_res_scale)*4, (int)(h*collide_res_scale)*4), (float)(x-w), (float)(y-w), (float)w*4, (float)h*4)
{

}

void GPUCollider::set_pos(double x_in, double y_in) {
    x = x_in;
    y = y_in;
    pixels.x = floor((float)x, pixels.get_pixel_width()) - (float)width;
    pixels.y = floor((float)y, pixels.get_pixel_height()) - (float)height;
}

Manifold GPUCollider::get_manifold() {
    FrameBuffer& pixels_fb = *this->pixels.frame_buffer;
    static std::vector<float> pixels_array;
    pixels_fb.write_to(pixels_array);
    
    assert(sum_squares.get_height() == pixels_fb.get_height() && sum_squares.get_width() == pixels_fb.get_width());

    sum_squares.populate([&](int x, int y) -> double {
            if (x < 0 || x >= pixels_fb.get_width() || y < 0 || y >= pixels_fb.get_height())
                return 0;
            else
                return 1 - pixels_array[(x + y*pixels_fb.get_width())*4];
        }, pixels_fb.get_width()/4, pixels_fb.get_height()/4);
    
    // The coordinates of the lower left pixel of the player in 'pixels'
    int origin_x = pixels_fb.get_width()/4;
    int origin_y = pixels_fb.get_height()/4;

    auto cost_function = [&] (int x, int y) -> double {
        if (sum_squares.get_sum(x, y) != 0)
            return 1000000;
        else {
            return abs(origin_x - x) + abs(origin_y - y);
        }
    };
    
    int min_px_x = origin_x;
    int min_px_y = origin_y;

    // Iterating through every point in the box around the lower left corner of
    // the player.
    for (int px_x = 0; px_x < (pixels_fb.get_width()/4)*2; px_x++) {
        for (int px_y = 0; px_y < (pixels_fb.get_height()/4)*2; px_y++) {
            if (cost_function(px_x, px_y) < cost_function(min_px_x, min_px_y)) {
                min_px_x = px_x;
                min_px_y = px_y;
            }
        }
    }

    glm::vec4 coll = glm::inverse(pixels.world_to_pixel()) * glm::vec4(min_px_x, min_px_y, 0, 1);

    
    Manifold m;

    m.norm_x = coll.x - x;
    m.norm_y = coll.y - y;

    if (min_px_x == origin_x)
        m.norm_x = 0;

    if (min_px_y == origin_y)
        m.norm_y = 0;

    m.cost = cost_function(min_px_x, min_px_y);

    if (m.norm_x < 0)
        m.norm_x += 1/collide_res_scale;

    if (m.norm_y < 0)
        m.norm_y += 1/collide_res_scale;

    return m;
}

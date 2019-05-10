#include <math.h>
#include <glm/glm.hpp>

#include "gpu_collider.h"
#include "basic_buffer.h"
#include "vector_math.h"

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
    pixels.x = floor((float)x - (float)width, pixels.get_pixel_width());
    pixels.y = floor((float)y - (float)height, pixels.get_pixel_height());
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
    
    auto world_to_pixel = pixels.world_to_pixel();
    auto llc_pix_loc = world_to_pixel*glm::vec4(this->x, this->y, 0, 1);
    double origin_x_d = llc_pix_loc.x;
    double origin_y_d = llc_pix_loc.y;
    // The coordinates of the lower left pixel of the player in 'pixels'
    int origin_x = pixels_fb.get_width()/4;
    int origin_y = pixels_fb.get_height()/4;

    double max_cost = 1000000;
    auto cost_function = [&] (int x, int y) -> double {
        if (x == -1 && y == -1) {
            if (sum_squares.get_sum(origin_x, origin_y) != 0 || 
                sum_squares.get_sum(origin_x+1, origin_y) != 0 ||
                sum_squares.get_sum(origin_x+1, origin_y+1) != 0 ||
                sum_squares.get_sum(origin_x, origin_y+1) != 0)
                return max_cost;
            else
                return 0;
        } else if (x == -1) {
            if (sum_squares.get_sum(origin_x, y) != 0 || 
                sum_squares.get_sum(origin_x+1, y) != 0)
                return max_cost;
            else
                return vec::mag_sq(0, origin_y_d - y);
        } else if (y == -1) {
            if (sum_squares.get_sum(x, origin_y) != 0 || 
                sum_squares.get_sum(x, origin_y+1) != 0)
                return max_cost;
            else
                return vec::mag_sq(origin_x_d - x, 0);
        } else {
            if (sum_squares.get_sum(x, y) != 0)
                return max_cost;
            else
                return vec::mag_sq(origin_x_d - x, origin_y_d - y);
        }
    };

    int min_px_x = origin_x;
    int min_px_y = origin_y;

    // Iterating through every pixel in the box around the lower left corner of
    // the player. The when px_x = -1 (or px_y = -1), it no longer refers to a
    // pixel, but the current x (or y) position of the player's lower left
    // corner.
    for (int px_x = -1; px_x <= (pixels_fb.get_width()/4)*2; px_x++) {
        for (int px_y = -1; px_y <= (pixels_fb.get_height()/4)*2; px_y++) {
            if (cost_function(px_x, px_y) < cost_function(min_px_x, min_px_y)) {
                min_px_x = px_x;
                min_px_y = px_y;
            }
        }
    }
    glm::vec4 coll = glm::inverse(world_to_pixel) * glm::vec4(min_px_x, min_px_y, 0, 1);

    Manifold m;

    m.norm_x = min_px_x == -1 ? 0 : coll.x - x;
    m.norm_y = min_px_y == -1 ? 0 : coll.y - y;


    m.cost = cost_function(min_px_x, min_px_y);
    return m;
}

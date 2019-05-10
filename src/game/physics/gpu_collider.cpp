#include <math.h>
#include <glm/glm.hpp>

#include "gpu_collider.h"
#include "basic_buffer.h"

#include "everything.h"

float round(float a, float inc) {
    return std::round(a/inc)*inc;
}

float floor(float a, float inc) {
    return std::floor(a/inc)*inc;
}

int floor_approx(double a) {
    return (int)std::floor(a+.00001);
}

int ceil_approx(double a) {
    return (int)std::ceil(a-.00001);
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

    assert(origin_x == (int)std::floor(origin_x_d));
    assert(origin_y == (int)std::floor(origin_y_d));

    //bool collide_ll = sum_squares.get_sum(
    //            floor_approx(origin_x_d), floor_approx(origin_y_d)) != 0;
    //bool collide_lr = sum_squares.get_sum(
    //            ceil_approx(origin_x_d), floor_approx(origin_y_d)) != 0;
    //bool collide_ul = sum_squares.get_sum(
    //            floor_approx(origin_x_d), ceil_approx(origin_y_d)) != 0;
    //bool collide_ur = sum_squares.get_sum(
    //            ceil_approx(origin_x_d), ceil_approx(origin_y_d)) != 0;
    //
    //bool is_colliding = collide_ll || collide_lr || collide_ul || collide_ur;
    
    double max_cost = 1000000;
    auto cost_function = [&] (int x, int y) -> double {
        if (x == -1 && y == -1) {
            if (sum_squares.get_sum(origin_x, origin_y) != 0 || 
                sum_squares.get_sum(origin_x+1, origin_y) != 0 ||
                sum_squares.get_sum(origin_x+1, origin_y+1) != 0 ||
                sum_squares.get_sum(origin_x, origin_y+1) != 0)
                return max_cost;
            else {
                return 0;
            }

        } else if (x == -1) {
            if (sum_squares.get_sum(origin_x, y) != 0 || 
                sum_squares.get_sum(origin_x+1, y) != 0)
                return max_cost;
            else
                return (origin_y_d - y)*(origin_y_d - y);
        } else if (y == -1) {
            if (sum_squares.get_sum(x, origin_y) != 0 || 
                sum_squares.get_sum(x, origin_y+1) != 0)
                return max_cost;
            else
                return (origin_x_d - x)*(origin_x_d - x);
        } else {
            if (sum_squares.get_sum(x, y) != 0)
                return max_cost;
            else {
                return (origin_x_d - x)*(origin_x_d - x) + (origin_y_d - y)*(origin_y_d - y);
            }
        }
    };

    int min_px_x = origin_x;
    int min_px_y = origin_y;

    // Iterating through every pixel in the box around the lower left corner of
    // the player.
    for (int px_x = -1; px_x <= (pixels_fb.get_width()/4)*2; px_x++) {
        for (int px_y = -1; px_y <= (pixels_fb.get_height()/4)*2; px_y++) {
            if (cost_function(px_x, px_y) < cost_function(min_px_x, min_px_y)) {
                min_px_x = px_x;
                min_px_y = px_y;
            }
        }
    }
    glm::vec4 coll = glm::inverse(world_to_pixel) * glm::vec4(min_px_x, min_px_y, 0, 1);

    static int count = 0;
    count++;
    //if (cost_function(min_px_x+1, min_px_y) == max_cost) {
    //    cout << "x right collide " << count << endl;
    //    cout << "(" << min_px_x << ", " << min_px_y << ")" << count << endl;
    //}

    //cout << cost_function(origin_x, origin_y) == max_cost && cost_function(origin_x+1, origin_y+1) << endl;
    //if (cost_function(min_px_x, min_px_y+1) == max_cost) {
    //    cout << "top collide " << count << endl;
    //    cout << "(" << min_px_x << ", " << min_px_y << ")" << count << endl;
    //}

    //bool is_colliding = false;
    //if (cost_function(origin_x, origin_y) == max_cost)
    //    is_colliding = true;


    Manifold m;

    m.norm_x = min_px_x == -1 ? 0 : coll.x - x;
    m.norm_y = min_px_y == -1 ? 0 : coll.y - y;
    //if (min_px_x == origin_x && min_px_y == origin_y) {
    //    cout << "BOTH " << count << endl;
    //} else if (min_px_x == origin_x) {
    //    cout << "x equal " << count << endl;
    //} else if (min_px_y == origin_y) {
    //    cout << "y equal " << count << endl;
    //}

    //if (collide_ll) {
    //    m.norm_y = std::max(m.norm_y, 0.0);
    //    m.norm_x = std::max(m.norm_x, 0.0);
    //}
    //if (collide_lr) {
    //    m.norm_y = std::max(m.norm_y, 0.0);
    //    m.norm_x = std::min(m.norm_x, 0.0);
    //}
    //if (collide_ur) {
    //    m.norm_y = std::min(m.norm_y, 0.0);
    //    m.norm_x = std::min(m.norm_x, 0.0);
    //}
    //if (collide_ul) {
    //    m.norm_y = std::min(m.norm_y, 0.0);
    //    m.norm_x = std::max(m.norm_x, 0.0);
    //}
    //if (!is_colliding) {
    //    m.norm_x = 0;
    //    m.norm_y = 0;
    //}
    //else {
        //assert(false);
        //cout << "COLLIDING" << count << endl;
        //cout << pixels.frame_buffer->get_width() << " " << pixels.frame_buffer->get_height() << endl;
        //cout << origin_x << ", " << origin_y << " " << cost_function(origin_x, origin_y) << endl;
        //cout << min_px_x << ", " << min_px_y << " " << cost_function(min_px_x, min_px_y) << endl;
        //assert(false);
    //}



    // TODO: This is an issue
    //if (min_px_x == origin_x)
        //m.norm_x = 0;

    //if (m.norm_x < -0.0001) {
    //    //cout << "HELLO " << count << endl;
    //    if (min_px_x == origin_x && cost_function(min_px_x+1, min_px_y) != max_cost)
    //        m.norm_x = 0;
    //} else if (m.norm_x > 0.0001) {
    //    if (min_px_x == origin_x)
    //        m.norm_x = 0;
    //}
    //
    //if (m.norm_y < -0.0001) {
    //    cout << "HELLO " << count << endl;
    //    if (min_px_y == origin_y && cost_function(min_px_x, min_px_y+1) != max_cost)
    //        m.norm_y = 0;
    //} else if (m.norm_x > 0.0001) {
    //    if (min_px_y == origin_y)
    //        m.norm_y = 0;
    //}

    //if (min_px_y == origin_y)
    //    m.norm_y = 0;

    m.cost = cost_function(min_px_x, min_px_y);

    //if (m.norm_x < 0)
    //    m.norm_x += 1/collide_res_scale;
    //
    //if (m.norm_y < 0)
    //    m.norm_y += 1/collide_res_scale;
    
    return m;
}

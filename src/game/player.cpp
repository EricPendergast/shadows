#include <algorithm>
#include <math.h>
#include <glm/glm.hpp>
#include <algorithm>

#include "poly.h"
#include "player.h"
#include "vector_math.h"
#include "everything.h"

float round(float a, float inc) {
    return std::round(a/inc)*inc;
}

float floor(float a, float inc) {
    return std::floor(a/inc)*inc;
}

Player::Player() : Player(64,64) {}
Player::Player(int w, int h) :
    pixels(new BasicBuffer((int)(w*collide_res_scale)*3, (int)(h*collide_res_scale)*3), (float)(x-w), (float)(y-w), (float)w*3, (float)h*3),
    sum_squares((int)(w*collide_res_scale)*3, (int)(h*collide_res_scale)*3),
    width(w),
    height(h),
    model({0,0,0,1,
           0,(float)h,0,1,
           (float)w,(float)h,0,1,
           0,0,0,1,
           0,0,0,1,
           0,0,0,1}) {
    }

void Player::draw() {
    model.sub_data(0, make_rect((float)x, (float)y, (float)width, (float)height));
    model.draw();
}

void Player::move(int direction_lr, bool jump, double time_step) {
    
    process_lr(direction_lr, time_step);
    
    dx += gravity_x*time_step;
    dy += gravity_y*time_step;
    
    if (jump && time_since_touched_platform < max_jump_delay)
        dy = -jump_speed;

    x += time_step*dx;
    y += time_step*dy;

    pixels.x = round((float)(x-width), pixels.get_pixel_width());
    pixels.y = round((float)(y-height), pixels.get_pixel_height());
    
    time_since_touched_platform += time_step;
}

Manifold Player::get_manifold() {
    FrameBuffer& pixels_fb = *this->pixels.frame_buffer;
    static std::vector<float> pixels_array;
    pixels_fb.write_to(pixels_array);
    
    assert(sum_squares.get_height() == pixels_fb.get_height() && sum_squares.get_width() == pixels_fb.get_width());

    sum_squares.populate([&](int x, int y) -> double {
            if (x < 0 || x >= pixels_fb.get_width() || y < 0 || y >= pixels_fb.get_height())
                return 0;
            else
                return 1 - pixels_array[(x + y*pixels_fb.get_width())*4];
        }, pixels_fb.get_width()/3, pixels_fb.get_height()/3);
    
    glm::mat4 world_to_pixel = pixels.world_to_pixel();


    auto cost_function = [&] (double x, double y) -> double {
        auto pos_in_square = world_to_pixel * glm::vec4(x, y, 0, 1);
        if (sum_squares.get_sum((int)std::floor(pos_in_square.x), (int)std::floor(pos_in_square.y)) != 0)
            return 1000000;
        else {
            return 0;
        }
    };
    
    // Lower left corner of the player.
    double ll_x = this->x;
    double ll_y = this->y + height;
    // Floor of lower left corner
    double llf_x = floor(ll_x, pixels.get_pixel_width()) + .00001;
    double llf_y = floor(ll_y, pixels.get_pixel_height()) + .00001;

    double min_x = llf_x;
    double min_y = llf_y;

    // Thw width and height of a pixel in sum_squares
    double inc_x = pixels.get_pixel_width();
    double inc_y = pixels.get_pixel_height();
    //double inc_x = 1;
    //double inc_y = 1;
    // Iterating through every point in the box around the lower left corner of
    // the player.
    // TODO: Set increment properly
    for (double x = llf_x - width; x < llf_x + width; x += inc_x) {
        for (double y = llf_y - height; y < llf_y + height; y += inc_y) {
            if (cost_function(x, y) < cost_function(min_x, min_y)) {
                min_x = x;
                min_y = y;
            }
        }
    }

    //if (min_x != ll_x)
    //    min_x = round(min_x, pixels.get_pixel_width());
    //
    //if (min_y != ll_y)
    //    min_y = round(min_y, pixels.get_pixel_height());
    Manifold m;

    if (min_x == llf_x)
        m.norm_x = 0;
    else
        m.norm_x = min_x - ll_x;
    
    if (min_x == llf_x)
        m.norm_y = 0;
    else
        m.norm_y = min_y - ll_y;

    m.cost = cost_function(min_x, min_y);
    if (m.norm_x != 0 || m.norm_y != 0) {
        m.cost = 10000000;
    //    //m.norm_x += std::fmod(this->x, inc_x);
    //    //m.norm_x += pixels.get_pixel_width() - std::fmod(this->x, pixels.get_pixel_width());
    //    m.norm_y += pixels.get_pixel_height() - std::fmod(this->y, pixels.get_pixel_height());
    }
    cout << "A " << m.norm_x << " " << m.norm_y << endl;
    cout << "B " << this->x << " " << this->y << endl;
    cout << "C " << inc_x << " " << inc_y << endl;
    return m;
}

void Player::collide(Manifold m) {
    // If pressing up against the surface
    if (vec::dot(dx, dy, m.norm_x, m.norm_y) < -.001) {
        vec::reject(&dx, &dy, m.norm_x, m.norm_y);
        vec::mult(&dx, &dy, .5);
    }
    
    // If surface normal and gravity are pointing in opposite directions
    if (vec::dot(gravity_x, gravity_y, m.norm_x, m.norm_y) < -.001) {
        time_since_touched_platform = 0;
    }
    
    if (m.cost > 999999) {
        std::cout << "DIE" << std::endl;
        //exit(1);
    }
    
    this->x += m.norm_x;
    this->y += m.norm_y;
}

void Player::process_lr(int direction_lr, double time_step) {
    if (direction_lr == 1 && dx < max_move_speed) {
        dx = std::min(dx + get_lr_acceleration()*time_step, max_move_speed);
    } else if (direction_lr == -1 && dx > -max_move_speed) {
        dx = std::max(dx - get_lr_acceleration()*time_step, -max_move_speed);
    }
}

double Player::get_lr_acceleration() {
    return on_ground() ? ground_lr_acceleration : air_lr_acceleration;
}

bool Player::on_ground() {
    return time_since_touched_platform < max_jump_delay;
}

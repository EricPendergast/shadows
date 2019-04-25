#include <algorithm>
#include <math.h>
#include <glm/glm.hpp>

#include "poly.h"
#include "player.h"
#include "vector_math.h"

Player::Player() : Player(64,64) {}
Player::Player(int w, int h) :
    pixels(new BasicBuffer((int)(w*3*collide_res_scale), (int)(h*3*collide_res_scale)), (float)(x-w), (float)(y-w), (float)w*3, (float)h*3),
    sum_squares((int)(w*3*collide_res_scale), (int)(h*3*collide_res_scale)),
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

    pixels.x = (float)(x-width);
    pixels.y = (float)(y-height);
    
    time_since_touched_platform += time_step;
}

Manifold Player::get_manifold() {
    FrameBuffer& pixels = *this->pixels.frame_buffer;
    static std::vector<float> pixels_array;
    pixels.write_to(pixels_array);
    
    assert(sum_squares.get_height() == pixels.get_height() && sum_squares.get_width() == pixels.get_width());

    sum_squares.populate([&](int x, int y) -> double {
            if (x < 0 || x >= pixels.get_width() || y < 0 || y >= pixels.get_height())
                return 0;
            else
                return 1 - pixels_array[(x + y*pixels.get_width())*4];
        }, pixels.get_width()/3, pixels.get_height()/3);
    
    glm::mat4 world_to_pixel = this->pixels.world_to_pixel();

    // Lower left corner of the player.
    double ll_x = this->x;
    double ll_y = this->y + height;

    auto cost_function = [&] (double x, double y) -> double {
        auto pos_in_square = world_to_pixel * glm::vec4(x, y, 0, 1);
        if (sum_squares.get_sum((int)pos_in_square.x, (int)pos_in_square.y) != 0)
            return 1000000;
        else {
            return (double)((ll_x-x)*(ll_x-x) + (ll_y-y)*(ll_y-y));
        }
    };
    
    double min_x = ll_x;
    double min_y = ll_y;

    // Iterating through every point in the box around the lower left corner of
    // the player.
    // TODO: Set increment properly
    for (double x = ll_x - width; x < ll_x + width; x++) {
        for (double y = ll_y - height; y < ll_y + height; y++) {
            if (cost_function(x, y) < cost_function(min_x, min_y)) {
                min_x = x;
                min_y = y;
            }
        }
    }

    Manifold m;
    m.norm_x = min_x - ll_x;
    m.norm_y = min_y - ll_y;
    m.cost = cost_function(min_x, min_y);
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

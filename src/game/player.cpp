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
        dy = jump_speed;

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
    
    // The coordinates of the lower left pixel of the player in 'pixels'
    int origin_x = pixels_fb.get_width()/3;
    int origin_y = pixels_fb.get_height()/3;

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
    // TODO: Set increment properly
    for (int px_x = 0; px_x < (pixels_fb.get_width()/3)*2; px_x++) {
        for (int px_y = 0; px_y < (pixels_fb.get_height()/3)*2; px_y++) {
            if (cost_function(px_x, px_y) < cost_function(min_px_x, min_px_y)) {
                min_px_x = px_x;
                min_px_y = px_y;
            }
            //cout << px_x << " " << px_y << endl;
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
    if (m.norm_x != 0 || m.norm_y != 0) {
        m.cost = 10000000;
    //    //m.norm_x += std::fmod(this->x, inc_x);
    //    //m.norm_x += pixels.get_pixel_width() - std::fmod(this->x, pixels.get_pixel_width());
    //    m.norm_y += pixels.get_pixel_height() - std::fmod(this->y, pixels.get_pixel_height());
    }
    cout << "A " << m.norm_x << " " << m.norm_y << endl;
    cout << "A'' " << x << " " << y << endl;
    cout << "B " << min_px_x << " " << min_px_y << endl;
    cout << "B' " << glm::to_string(coll) << endl;
    cout << "C " << origin_x << " " << origin_y << endl;
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

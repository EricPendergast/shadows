#include <algorithm>
#include <math.h>

#include "player.h"
#include "vector_math.h"

Player::Player() : Player(64,64) {}
Player::Player(int w, int h) : pixels(w*3, h*3), sum_squares(w*3, h*3), width(w), height(h) {}

void Player::draw(Drawer* drawer) const {
    drawer->draw_quad(
            (int)(x + 0),       (int)(y + 0),
            (int)(x + width),   (int)(y + 0),
            (int)(x + width),   (int)(y + height),
            (int)(x + 0),       (int)(y + height));
}

void Player::draw() {
    // TODO: Not implemented
}

void Player::move(int direction_lr, bool jump, double time_step) {
    
    process_lr(direction_lr, time_step);
    
    dx += gravity_x*time_step;
    dy += gravity_y*time_step;
    
    if (jump && time_since_touched_platform < max_jump_delay)
        dy = -jump_speed;
    
    x += time_step*dx;
    y += time_step*dy;
    
    time_since_touched_platform += time_step;
}

void Player::collide() {
    static std::vector<float> pixels_array;
    pixels.write_to(pixels_array);
    
    sum_squares.populate([&](int x, int y) -> double {
            if (x < 0 || x >= pixels.get_width() || y < 0 || y >= pixels.get_height())
                return 0;
            else
                return 1 - pixels_array[(x + (pixels.get_height()-1-y)*pixels.get_width())*4];
        }, pixels.get_width()/3, pixels.get_height()/3);
    
    // Takes in coordinates relative to the lower left corner of player, in
    // world scale. range is x in [-width, width], y in [-height, height]
    auto cost_function = [&] (int x, int y) -> double {
            int x_in_square = (int)((x/(double)width + 1)*pixels.get_width()/3);
            int y_in_square = (int)((y/(double)height + 1)*pixels.get_height()/3);
            if (sum_squares.get_sum(x_in_square, y_in_square) != 0)
                return 1000000;
            else {
                return (double)(x*x + y*y);
            }
        };
    
    int min_x = 0, min_y = 0;
    
    for (int x = -width; x < width; x++) {
        for (int y = -height; y < height; y++) {
            if (cost_function(x, y) < cost_function(min_x, min_y)) {
                min_x = (int)x;
                min_y = (int)y;
            }
        }
    }
    
    // If pressing up against the surface
    if (vec::dot(dx, dy, min_x, min_y) < -.001) {
        vec::reject(&dx, &dy, min_x, min_y);
        vec::mult(&dx, &dy, .5);
    }
    
    // If surface normal and gravity are pointing in opposite directions
    if (vec::dot(gravity_x, gravity_y, min_x, min_y) < -.001) {
        time_since_touched_platform = 0;
        last_push_x = min_x;
        last_push_y = min_y;
    }
    
    if (cost_function(min_x, min_y) > 999999) {
        std::cout << "DIE" << std::endl;
    }
    
    this->x += min_x;
    this->y += min_y;
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

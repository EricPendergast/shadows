#include "player.h"
#include <math.h>
#include "vector_math.h"

Player::Player() : Player(64,64) {}
Player::Player(int w, int h) : pixels(w*3, h*3), sum_squares(w*3, h*3), width(w), height(w) {}

void Player::draw() {
    glBegin(GL_QUADS);
    glVertex2i((int)(x + 0),       (int)(y + 0));
    glVertex2i((int)(x + width),   (int)(y + 0));
    glVertex2i((int)(x + width),   (int)(y + height));
    glVertex2i((int)(x + 0),       (int)(y + height));
    glEnd();
}

void Player::move(int direction_lr, int direction_ud, bool jump, double time_step) {
    (void)direction_ud;
    
    if (direction_lr != 0)
        dx = move_speed*(double)direction_lr;
    
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
                return (double)(x*x + y*y) + vec::angle(x, y, dx, dy)*5;
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
    
    if (vec::dot(dx, dy, min_x, min_y) < -.001) {
        vec::reject(&dx, &dy, min_x, min_y);
        vec::mult(&dx, &dy, .5);
    }
    
    if (vec::dot(gravity_x, gravity_y, min_x, min_y) < -.001) {
        time_since_touched_platform = 0;
    }
    
    this->x += min_x;
    this->y += min_y;
}

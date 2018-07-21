#include "player.h"
#include <math.h>

Player::Player() : pixels(64*3, 64*3), sum_squares(64*3, 64*3) {
}

void Player::draw() {
    glBegin(GL_QUADS);
    glVertex2f((int)(x + 0),       (int)(y + 0));
    glVertex2f((int)(x + width),   (int)(y + 0));
    glVertex2f((int)(x + width),   (int)(y + height));
    glVertex2f((int)(x + 0),       (int)(y + height));
    glEnd();
}

void Player::move(int direction_lr, int direction_ud, bool jump, double time_step) {
    dx = move_speed*(double)direction_lr;
    
    // TODO: What should this be multiplied by?
    //dy = move_speed*(double)direction_ud;
    dy += gravity*time_step;
    
    if (jump)
        dy = -jump_speed;
    
    x += time_step*dx;
    y += time_step*dy;
    
    //std::cout << "x y " << x << " " << y << std::endl;
    //std::cout << "dx dy " << dx << " " << dy << std::endl;
}

void Player::collide() {
    std::vector<float> pixels_array;
    pixels.write_to(pixels_array);
    
    sum_squares.populate([&](int x, int y) -> float {
            if (x < 0 || x >= pixels.get_width() || y < 0 || y >= pixels.get_height())
                return 0;
            else
                return 1 - pixels_array[(x + (pixels.get_height()-1-y)*pixels.get_width())*4];
        }, pixels.get_width()/3, pixels.get_height()/3);
    
    // Takes in coordinates relative to the lower left corner of player, in
    // world scale. range is x in [-width, width], y in [-height, height]
    auto cost_function = [&] (float x, float y) -> float {
            int x_in_square = (int)((x/width + 1)*(float)pixels.get_width()/3);
            int y_in_square = (int)((y/height + 1)*(float)pixels.get_height()/3);
            if (sum_squares.get_sum(x_in_square, y_in_square) != 0)
                return 1000000;
            else {
                return x*x + y*y;
            }
        };
    
    float min_x = 0, min_y = 0;
    
    for (float x = -width; x < width; x++) {
        for (float y = -height; y < height; y++) {
            if (cost_function(x, y) < cost_function(min_x, min_y)) {
                min_x = x;
                min_y = y;
            }
        }
    }
    
    dx += min_x/2;
    dy += min_y/2;
    this->x += min_x;
    this->y += min_y;
    
    //std::cout << "Collision: " << cost_function(min_x, min_y) << "  " << min_x << " " << min_y << std::endl;
    //std::cout << "x y " << x << " " << y << std::endl;
    //std::cout << "dx dy " << dx << " " << dy << std::endl;
}

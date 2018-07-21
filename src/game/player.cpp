#include "player.h"
#include <math.h>

Player::Player() : pixels(64, 64), sum_squares(64, 64) {
}

void Player::draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBegin(GL_QUADS);
    glVertex2f((float)x + 0,  (float)y + 0);
    glVertex2f((float)x + 50, (float)y + 0);
    glVertex2f((float)x + 50, (float)y + 50);
    glVertex2f((float)x + 0,  (float)y + 50);
    glEnd();
}

void Player::move(int direction_lr, int direction_ud, bool jump, double time_step) {
    dx = move_speed*(double)direction_lr;
    
    // TODO: What should this be multiplied by?
    //dy += gravity;
    dy = move_speed*(double)direction_ud;
    
    if (jump)
        dy = -jump_speed;
    
    x += time_step*dx;
    y += time_step*dy;
    
    collide();
}

void Player::collide() {
    //static int count = 0;
    std::vector<float> asdf;
    pixels.write_to(asdf);
    
    sum_squares.populate([&](int x, int y) -> float {
            if (x < 0 || x >= pixels.get_width() || y < 0 || y >= pixels.get_height())
                return 0;
            else
                return 1 - asdf[(x + y*64)*4];
        });
    
    bool found = false;
    int min_x = 0, min_y = 0;
    for (int x = 0; x < pixels.get_width(); x++) {
        for (int y = 0; y < pixels.get_height(); y++) {
            if (sum_squares.get_sum(x, y) == 0 && (!found || x*x + y*y < min_x*min_x + min_y*min_y)) {
                found = true;
                min_x = x;
                min_y = y;
            }
        }
    }
    //x += min_x/(64/3)*50 - 50;
    x += min_x;
    //x -= min_y/(64/3)*50 - 50;
    y -= min_y;
    x = round(x);
    y = round(y);
    
    std::cout << sum_squares.get_sum(min_x, min_y) << "  " << min_x << " " << min_y << std::endl;
}

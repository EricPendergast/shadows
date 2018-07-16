#include "player.h"

Player::Player() : pixels_around_player(64, 64) {
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
    static int count = 0;
    std::vector<float> asdf;
    pixels_around_player.write_to(asdf);
    
    for (float f : asdf) {
        if (f == 0) {
            std::cout << f << "Collide " << count++ << std::endl;
            break;
        }
    }
}

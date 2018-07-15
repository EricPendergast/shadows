#include "player.h"

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
}

void Player::collide(FrameBuffer& map) {
    static int count = 0;
    if (map.read_pixel((int)x,500 - (int)y)[0] == 0)
        std::cout << "Collide " << count++ << std::endl;
}

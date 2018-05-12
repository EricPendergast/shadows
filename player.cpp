#include "player.h"
#include "opengl_context.h"

void Player::draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBegin(GL_QUADS);
    glVertex2f((float)x + 0,  (float)y + 0);
    glVertex2f((float)x + 50, (float)y + 0);
    glVertex2f((float)x + 50, (float)y + 50);
    glVertex2f((float)x + 0,  (float)y + 50);
    glEnd();
}

void Player::move(int direction_lr, bool jump, double time_step) {
    dx = move_speed*(double)direction_lr;
    
    // TODO: What should this be multiplied by?
    dy += gravity;
    
    if (jump)
        dy = -jump_speed;
    
    x += time_step*dx;
    y += time_step*dy;
    //std::cout << y << std::endl;
}

#include "player.h"
#include "opengl_context.h"

void Player::draw() {
    x += dx;
    y += dy;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBegin(GL_QUADS);
    glVertex2f(x + 0,  y + 0);
    glVertex2f(x + 50, y + 0);
    glVertex2f(x + 50, y + 50);
    glVertex2f(x + 0,  y + 50);
    glEnd();
}

void Player::move(int direction_lr, bool jump) {
    dx = 1.0f*(float)direction_lr;
}

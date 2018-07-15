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
    //std::cout << y << std::endl;
}

void Player::collide(FrameBuffer& map) {
    //map.write_to_tga_file("debug_output/asdf.tga");
    static int count = 0;
    if (map.read_pixel((int)x,(int)y)[0] == 0)
        std::cout << "Collide " << count++ << std::endl;
    //for (int i = 0; i < 500; i++) {
    //    for (int j = 0; j < 500; j++) {
    //        if (map.read_pixel(i,j)[0] == 0) {
    //            std::cout << "HERE" << i << " " << j << "\n";
    //        }
    //    }
    //}
    std::cout << map.read_pixel(390,293)[0] << "\n";
}

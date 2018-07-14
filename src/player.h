#ifndef PLAYER_H
#define PLAYER_H

#include "depth_box_buffer.h"
#include "opengl_context.h"

// Speeds are in units of world coordinates per second.
class Player {
public:
    // 'direction_lr' specifies the direction the player is trying to move and
    // 'jump' specifies whether the player just tried to jump.
    void move(int direction_lr, bool jump, double time_step);
    void collide(FrameBuffer& map);
    void draw();
private:
    
    double x = 0;
    double y = 0;
    double dx = 0;
    double dy = 0;
    
    double move_speed = 200;
    double gravity = 10;
    double jump_speed = 500;
    
};

#endif

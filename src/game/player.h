#pragma once

#include "depth_box_buffer.h"
#include "opengl_context.h"
#include "basic_buffer.h"

// Speeds are in units of world coordinates per second.
class Player {
public:
    BasicBuffer pixels_around_player;
    Player();
    // 'direction_lr' specifies the direction the player is trying to move and
    // 'jump' specifies whether the player just tried to jump.
    void move(int direction_lr, int direction_ud, bool jump, double time_step);
    void collide();
    void draw();
    // TODO: make private
    double x = 0;
    double y = 0;
    double dx = 0;
    double dy = 0;
private:
    
    
    double move_speed = 200;
    double gravity = 10;
    double jump_speed = 500;
};

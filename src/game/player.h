#pragma once

#include "depth_box_buffer.h"
#include "opengl_context.h"
#include "basic_buffer.h"
#include "sum_squares.h"

// Speeds are in units of world coordinates per second.
class Player {
public:
    BasicBuffer pixels;
    SumSquares<double> sum_squares;
    Player();
    Player(int w, int h);
    // 'direction_lr' specifies the direction the player is trying to move and
    // 'jump' specifies whether the player just tried to jump.
    void move(int direction_lr, int direction_ud, bool jump, double time_step);
    void draw();
    // TODO: make private
    double x = 0;
    double y = 0;
    double dx = 0;
    double dy = 0;
    int width = 64;
    int height = 64;
    void collide(double time_step);
private:
    double move_speed = 400;
    double gravity = 800;
    double jump_speed = 500;
};

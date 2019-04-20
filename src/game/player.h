#ifndef SRC_GAME_PLAYER_H
#define SRC_GAME_PLAYER_H

#include "depth_box_buffer.h"
#include "opengl_context.h"
#include "basic_buffer.h"
#include "sum_squares.h"
#include "drawer.h"
#include "vbo.h"
#include "collision_map.h"

// Speeds are in units of world coordinates per second.
class Player : Drawable {
public:
    WorldFrameBuffer pixels;
    SumSquares<double> sum_squares;
    double x = 5;
    double y = 5;
    double dx = 0;
    double dy = 0;
    int width = 64;
    int height = 64;
    VBO model;
    Player();
    Player(int w, int h);
    // 'direction_lr' specifies the direction the player is trying to move and
    // 'jump' specifies whether the player just tried to jump.
    void move(int direction_lr, bool jump, double time_step);
    void draw();
    // TODO: make private
    void collide();
private:
    double max_move_speed = 250;
    double ground_lr_acceleration = 100000;
    double air_lr_acceleration = 1000;
    double gravity_x = 0;
    double gravity_y = 1200;
    double jump_speed = 500;
    
    double last_push_x = 0;
    double last_push_y = 0;
    
    // Number of seconds between stopping touching a platform and being able to
    // jump.
    double max_jump_delay = .05;
    double time_since_touched_platform = 1000000;
    
    void process_lr(int direction_lr, double time_step);
    
    double get_lr_acceleration();
    bool on_ground();
};

#endif

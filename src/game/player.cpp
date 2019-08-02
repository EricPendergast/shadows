#include <algorithm>
#include <math.h>
#include <glm/glm.hpp>
#include <algorithm>

#include "poly.h"
#include "player.h"
#include "vector_math.h"
#include "everything.h"

Player::Player() : Player(64,64) {}
Player::Player(int w, int h) :
    collider(1/4.0f, w, h),
    width(w),
    height(h),
    model({0,0,0,1,
           0,(float)h,0,1,
           (float)w,(float)h,0,1,
           0,0,0,1,
           0,0,0,1,
           0,0,0,1}) {
    }

void Player::control(const ControlInputs& controls) {
    this->controls = controls;
}

void Player::update(double time_step, std::function<void(WorldFrameBuffer&)> drawCollider) {
    drawCollider(collider.pixels);

    collide(get_manifold());
    process_lr(controls.direction_lr, time_step);
    
    dx += gravity_x*time_step;
    dy += gravity_y*time_step;
    
    if (controls.jump && time_since_touched_platform < max_jump_delay)
        dy = jump_speed;

    x += time_step*dx;
    y += time_step*dy;

    collider.set_pos(x, y);
    
    time_since_touched_platform += time_step;
}

// TODO: This should bind the buffer, set world_to_screen, bind a shader.
void Player::render(WorldFrameBuffer& render_to) {
    model.sub_data(0, make_rect((float)x, (float)y, (float)width, (float)height));
    model.draw();
}

Manifold Player::get_manifold() {
    return collider.get_manifold();
}

void Player::process_lr(int direction_lr, double time_step) {
    if (direction_lr == 1 && dx < max_move_speed) {
        dx = std::min(dx + get_lr_acceleration()*time_step, max_move_speed);
    } else if (direction_lr == -1 && dx > -max_move_speed) {
        dx = std::max(dx - get_lr_acceleration()*time_step, -max_move_speed);
    }
}

void Player::collide(Manifold m) {
    // If pressing up against the surface
    if (vec::dot(dx, dy, m.norm_x, m.norm_y) < -.001) {
        vec::reject(&dx, &dy, m.norm_x, m.norm_y);
        vec::mult(&dx, &dy, .5);
    }
    
    // If surface normal and gravity are pointing in opposite directions
    if (vec::dot(gravity_x, gravity_y, m.norm_x, m.norm_y) < -.001) {
        time_since_touched_platform = 0;
    }
    
    if (m.cost > 999999) {
        std::cout << "DIE" << std::endl;
        dx = -dx;
        dy = -dy;
        return;
        //exit(1);
    }
    
    this->x += m.norm_x;
    this->y += m.norm_y;
}

double Player::get_lr_acceleration() {
    return on_ground() ? ground_lr_acceleration : air_lr_acceleration;
}

bool Player::on_ground() {
    return time_since_touched_platform < max_jump_delay;
}

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
    shader("shaders/player.vert", "shaders/player.frag"),
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

void Player::render(WorldFrameBuffer& render_to) {
    shader.use();

    auto world_to_screen = render_to.world_to_screen();
    shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(world_to_screen));
    model.sub_data(0, make_rect((float)x, (float)y, (float)width, (float)height));
    model.draw();
}

bool Player::can_interact(const Interactable& interactable) {
    auto [i_x, i_y] = interactable.get_position();
    return i_x >= x && i_x <= x + width && i_y >= y && i_y <= y + height;
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

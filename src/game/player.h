#ifndef SRC_GAME_PLAYER_H
#define SRC_GAME_PLAYER_H

#include "depth_box_buffer.h"
#include "opengl_context.h"
#include "basic_buffer.h"
#include "sum_squares.h"
#include "vbo.h"
#include "world_frame_buffer.h"
#include "manifold.h"
#include "gpu_collider.h"
#include "game_object_interfaces.h" 

// Speeds are in units of world coordinates per second.
class Player : public Physical, public Renderable, public UserControllable {
public:
    Player();
    Player(int w, int h);
    void control(const ControlInputs& controls) override;
    void update(double timestep, std::function<void(WorldFrameBuffer&)> drawCollider) override;
    void render(WorldFrameBuffer& render_to) override;
private:
    GPUCollider collider;
    VBO model;
    ControlInputs controls;
    ShaderProgram shader;

    double x = 5;
    double y = 5;
    double dx = 0;
    double dy = 0;
    double width = 64;
    double height = 64;
    double max_move_speed = 350;
    double ground_lr_acceleration = 100000;
    double air_lr_acceleration = 1000;
    double gravity_x = 0;
    double gravity_y = -1500;
    double jump_speed = 700;
    
    double last_push_x = 0;
    double last_push_y = 0;
    
    // Number of seconds between stopping touching a platform and being able to
    // jump.
    double max_jump_delay = .1;
    double time_since_touched_platform = 1000000;

    void process_lr(int direction_lr, double time_step);
    double get_lr_acceleration();
    bool on_ground();
    void collide(Manifold m);
    Manifold get_manifold();
};

#endif

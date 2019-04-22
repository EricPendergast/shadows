#include "player.h"
#include "light.h"
#include "world.h"
#include "frame_buffer.h"
#include "world_frame_buffer.h"

class Level {
    WorldFrameBuffer render_to;
    ShaderProgram main_shader;
public:
    Light light;
private:
    World world;
    Player player;
    static float a;

public:
    Level();
    void update(double timestep, int player_lr, bool player_jump);

    Manifold get_player_manifold();
    void render();
    void set_render_target(FrameBuffer* render_to);
    // Takes normalized device coordinates
    void on_mouse_press(float ndc_x, float ndc_y);
};

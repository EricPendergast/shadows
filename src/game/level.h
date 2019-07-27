#include "player.h"
#include "light.h"
#include "world.h"
#include "frame_buffer.h"
#include "world_frame_buffer.h"

class Level {
public:
    Level();
    void update(double timestep, int player_lr, bool player_jump);

    Manifold get_player_manifold();
    void render();
    void update_viewport();
    void set_render_target(FrameBuffer* render_to);
    // Takes normalized device coordinates
    void on_mouse_press(float ndc_x, float ndc_y);
    Light light1;
    Light light2;

private:
    WorldFrameBuffer render_to;
    ShaderProgram main_shader;
    World world;
    Player player;
    static float a;
};

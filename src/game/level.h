#include "player.h"
#include "light.h"
#include "frame_buffer.h"
#include "world_frame_buffer.h"
#include "game_object_interfaces.h"
#include "light_set.h"

class Level {
public:
    Level();
    void update(double timestep, int player_lr, bool player_jump);

    void render();
    void update_viewport();
    void set_render_target(FrameBuffer* render_to);
    // Takes normalized device coordinates
    void on_mouse_press(float ndc_x, float ndc_y);
private:
    // TODO: Remove most of these
    WorldFrameBuffer render_to;
    ShaderProgram main_shader;
    static float a;

    GameObjects objs;
    LightSet light_set;

    // This exists as a bandaid solution for controling the camera
    std::shared_ptr<Player> player;
};

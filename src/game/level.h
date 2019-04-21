#include "player.h"
#include "light.h"
#include "world.h"
#include "frame_buffer.h"
#include "world_frame_buffer.h"

class Level {
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
    void render(FrameBuffer* render_to);
};

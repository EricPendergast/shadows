#include "player.h"
#include "light.h"
#include "world.h"
#include "frame_buffer.h"
#include "collision_map.h"

class Level {
    ShaderProgram main_shader;

    WorldFrameBuffer collision_map;
public:
    Light light;
private:
    World world;
    Player player;
    static float a;

public:
    Level();
    void update(double timestep, int player_lr, bool player_jump);

    void render(FrameBuffer* render_to);
};

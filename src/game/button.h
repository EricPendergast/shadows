#include "game_object_interfaces.h"
#include "vbo.h"
#include "shader.h"

class Button : public Renderable, public Interactable {
public:
    Button(int x, int y);
    
    void render(WorldFrameBuffer& render_to) override;
    void do_action(Interactor& interactor) override;
    std::pair<double, double> get_position() const override;
private:
    int x = 0;
    int y = 0;
    VBO model;
    ShaderProgram shader;
};

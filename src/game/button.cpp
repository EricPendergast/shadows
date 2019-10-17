#include "button.h"
#include "everything.h"
#include "poly.h"

Button::Button(int x, int y) :
    x(x), y(y), 
    model(make_rect(x, y, 10, 10)),
    shader("shaders/main.vert", "shaders/main.frag")
    {}

void Button::render(WorldFrameBuffer& render_to) {
    // TODO: Same code is in Player::render
    shader.use();
    auto world_to_screen = render_to.world_to_screen();
    shader.set_uniform_Matrix4f("world_to_screen", glm::value_ptr(world_to_screen));
    model.draw();
}

void Button::do_action(Interactor& interactor) {
    cout << "Button press" << endl;
}

std::pair<double, double> Button::get_position() const {
    return {x, y};
}

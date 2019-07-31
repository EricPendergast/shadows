#include "light_set.h"
#include "raii.h"
#include <iostream>

LightSet::LightSet() :
    lights(2)
{
}

void LightSet::render(WorldFrameBuffer& render_to) {
    //std::cout << "Rendering " << (int64_t)this << std::endl;
    //lights[0].render(render_to);
    //{
    //    WithColorLogicOpEnabled w{true};
    //    WithLogicOp w2{GL_OR};
    //    lights[1].render(render_to);
    //}
}

void LightSet::generate_shadows(std::function<void()> drawOpaqueShapes) {
    //std::cout << "Generating shadows " << (int64_t)this << std::endl;
    //lights[0].generate_shadows(drawOpaqueShapes);
    //lights[1].generate_shadows(drawOpaqueShapes);
}

void LightSet::render_pixel_collider(WorldFrameBuffer& render_to) {
    //lights[0].render(render_to);
    //{
    //    WithColorLogicOpEnabled w{true};
    //    WithLogicOp w2{GL_OR};
    //    lights[1].render(render_to);
    //}
}

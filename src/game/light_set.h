#ifndef SRC_GAME_LIGHT_SET_H
#define SRC_GAME_LIGHT_SET_H


#include "game_object_interfaces.h"
#include "light.h"

class LightSet : public Renderable, public PixelCollidable, public ShadowCastable {
public:
    LightSet();
    /*virtual?*/ void render(WorldFrameBuffer& wfb) override;
    /*virtual?*/ void render_pixel_collider(WorldFrameBuffer& render_to) override;
    /*virtual?*/ void generate_shadows(std::function<void()> drawOpaqueShapes) override;

    std::vector<Light> lights;
private:

};

#endif

#ifndef SRC_GAME_GAME_OBJECT_INTERFACES_H
#define SRC_GAME_GAME_OBJECT_INTERFACES_H

#include "world_frame_buffer.h"

#include <vector>
#include <memory>
#include <functional>

class GameObject {
public:
    virtual ~GameObject() {}
};

// TODO: This doesn't account for objects that move but don't collide with
// stuff.
class Physical : virtual public GameObject {
public:
    virtual void update(double timestep, std::function<void(WorldFrameBuffer&)> drawCollider) = 0;
};

class Renderable : virtual public GameObject {
public:
    virtual void render(WorldFrameBuffer& render_to) = 0;
};

// TODO:
//class PickUpable;

class PixelCollidable : virtual public GameObject {
public:
    virtual void render_pixel_collider(WorldFrameBuffer& render_to) = 0;
};

class Opaque : virtual public GameObject {
public:
    virtual void draw_opaque_shape() = 0;
};

class ShadowCastable : virtual public GameObject {
public:
    virtual void generate_shadows(std::function<void()> drawOpaqueShapes) = 0;
};

// 'direction_lr' specifies the direction the player is trying to move and
// 'jump' specifies whether the player just tried to jump.
struct ControlInputs {
    int direction_lr;
    bool jump;
    int mouse_x = -1;
    int mouse_y = -1;
};

class UserControllable : virtual public GameObject {
public:
    virtual void control(const ControlInputs& controls) = 0;
};

struct GameObjects {
    std::vector<std::shared_ptr<Physical>> physicalObjs;
    std::vector<std::shared_ptr<Renderable>> renderableObjs;
    std::vector<std::shared_ptr<PixelCollidable>> pixelCollidableObjs;
    std::vector<std::shared_ptr<Opaque>> opaqueObjs;
    std::vector<std::shared_ptr<ShadowCastable>> shadowCastableObjs;
    std::vector<std::shared_ptr<UserControllable>> userControllableObjs;

    // Adds the passed in object to all the lists it can.
    void registerObj(std::shared_ptr<GameObject> gameObject);
};

#endif

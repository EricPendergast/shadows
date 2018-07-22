#include "drawer.h"

#pragma once

// This class is in charge of managing the position of blocks or various
// objects in the background of the world.
class World : Drawable {
public:
    World();
    void draw(Drawer* drawer) const;
};

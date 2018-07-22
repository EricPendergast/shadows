#include "world.h"

World::World(){}

// Only draws polygons. Uses world coordinates.
void World::draw(Drawer* drawer) const {
    drawer->draw_quad(450, 300,
                      400, 300,
                      400, 350,
                      450, 350);
    
    drawer->draw_quad(0,   500,
                      400, 500,
                      400, 490,
                      0,   490);
}


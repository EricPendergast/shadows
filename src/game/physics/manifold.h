#ifndef SRC_GAME_PHYSICS_MANIFOLD_H
#define SRC_GAME_PHYSICS_MANIFOLD_H

struct Manifold {
    double norm_x = 0, norm_y = 0;
    double cost = -1;
};

#endif

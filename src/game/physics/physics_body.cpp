#include "physics_body.h"

void PhysicsBody::update(double time_step) {
    x += time_step*dx;
    y += time_step*dy;
}

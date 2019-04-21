#include "poly.h"

std::vector<GLfloat> make_rect(GLfloat x, GLfloat y, GLfloat w, GLfloat h) {
    return {x, y, 0, 1,
            x+w, y, 0, 1,
            x, y+h, 0, 1,
            x, y+h, 0, 1,
            x+w, y+h, 0, 1,
            x+w, y, 0, 1};
}

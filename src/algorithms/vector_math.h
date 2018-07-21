#include <math.h>
#include <iostream>

namespace vec {
    void mult(double* x, double* y, double m) {
        *x *= m;
        *y *= m;
    }
    double mag_sq(double x, double y) {
        return x*x + y*y;
    }
    
    double mag(double x, double y) {
        return sqrt(mag_sq(x, y));
    }
    
    double dot(double x1, double y1, double x2, double y2) {
        return x1 * x2 + y1 * y2;
    }
    
    void project(double* proj_x, double* proj_y, double onto_x, double onto_y) {
        double scale = dot(*proj_x, *proj_y, onto_x, onto_y)/mag_sq(onto_x, onto_y);
        *proj_x = onto_x * scale;
        *proj_y = onto_y * scale;
    }
    
    void reject(double* rej_x, double* rej_y, double onto_x, double onto_y) {
        double proj_x = *rej_x;
        double proj_y = *rej_y;
        project(&proj_x, &proj_y, onto_x, onto_y);
        *rej_x -= proj_x;
        *rej_y -= proj_y;
    }
    
    double angle(double x1, double y1, double x2, double y2) {
        return acos(dot(x1, y1, x2, y2)/(mag(x1, y1)*mag(x2, y2)));
    }
}

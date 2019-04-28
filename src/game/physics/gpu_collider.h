#include "manifold.h"
#include "world_frame_buffer.h"
#include "sum_squares.h"

class GPUCollider {
    // In world coordinates
    double x, y, width, height;
    double collide_res_scale = 1;

    SumSquares<double> sum_squares;
public:
    WorldFrameBuffer pixels;
    GPUCollider(double resolution, double w, double h);
    void set_pos(double x_in, double y_in);
    Manifold get_manifold();
};

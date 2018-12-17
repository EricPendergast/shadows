#include "frame_buffer.h"

// Holds a frame buffer which corresponds to an actual position in world
// coordinates.

class WorldBuffer {
private:
    FrameBuffer raw_buffer;
    // World positions
    double x, y, w, h;
public:
    WorldBuffer(FrameBuffer rb, double x_in, double y_in, double w_in, double h_in) : raw_buffer(rb),  {
        
    }
};

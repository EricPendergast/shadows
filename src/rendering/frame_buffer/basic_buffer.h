#ifndef SRC_RENDERING_FRAME_BUFFER_BASIC_BUFFER_H
#define SRC_RENDERING_FRAME_BUFFER_BASIC_BUFFER_H

#include "frame_buffer.h"


// A frame buffer which is as simple as possible. No depth testing, or anything
// fancy.
class BasicBuffer : public FrameBuffer {
public:
    BasicBuffer(int w, int h);
};


#endif

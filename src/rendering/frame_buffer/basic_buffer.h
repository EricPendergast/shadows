#include "frame_buffer.h"

#pragma once

// A frame buffer which is as simple as possible. No depth testing, or anything
// fancy.
class BasicBuffer : public FrameBuffer {
public:
    BasicBuffer(int w, int h);
};


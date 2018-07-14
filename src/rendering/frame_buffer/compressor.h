#include "basic_buffer.h"

class Compressor {
    int in_width, in_height;
    int out_width, out_height;
    BasicBuffer intermediate;
    BasicBuffer out;
    ShaderProgram compression_shader;
public:
    // Specify the width that the input will always be
    Compressor(int w_i, int h_i, int w_o, int h_o, ShaderProgram compression_shader_in);
    
    void compress(FrameBuffer* source);
};

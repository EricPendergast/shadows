#include "compressor.h"
#include <assert.h>

Compressor::Compressor(int w_i, int h_i, int w_o, int h_o, ShaderProgram compression_shader_in):
        in_width(w_i), in_height(h_i),
        out_width(w_o), out_height(h_o),
        intermediate(w_i, h_i),
        out(w_o, h_o),
        compression_shader(compression_shader_in) {
            
        // These asserts may be temporary.
        assert(w_i == h_i && w_o == h_o);
        while (w_i > 1) {
            assert(w_i % 2 == 0);
            w_i /= 2;
            if (w_i == w_o)
                break;
        }
        assert(w_i == w_o);
    }

void Compressor::compress(FrameBuffer* source) {
    assert(source->get_width() == in_width && source->get_height() == in_height);
    
}

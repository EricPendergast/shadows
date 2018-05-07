#version 450
// Assumes coordinates passed in are world
// coordinates.

uniform vec2 light_pos;

// Says which side of the projection square to project onto
uniform int side;

// Note: These are the same values as defined in DepthBoxBuffer in
// frame_buffer.h
uniform int UP = 0;
uniform int DOWN = 1;
uniform int RIGHT = 2;
uniform int LEFT = 3;

layout(location = 0) in vec4 in_Position;

out vec3 rel_pos;

#define FLT_MIN 1.175494351e-38

float sign(float v) {
    return  v > 0.0 ? 1.0 : -1.0;
}

// Makes v be a very small number if it is zero, keeps it the same otherwise
float make_nonzero(float v) {
    return sign(v)*max(FLT_MIN, abs(v));
}

void main(void) {
    // Position relative to the light
    rel_pos = in_Position.xyz - vec3(light_pos,0);
    
    // gl_Position is the clip coordinate, so (say in the UP case), OpenGL
    // divides rel_pos.x by rel_pos.y to get the final vertex coordinate. The
    // reason this is not done manually by this shader is that this way
    // clipping is done automatically and we also get the correct depth
    // interpolation. 
    
    if (side == UP)
        gl_Position = vec4(rel_pos.x, 0,0, make_nonzero(rel_pos.y));
    else if (side == DOWN)
        gl_Position = vec4(rel_pos.x, 0,0, make_nonzero(-rel_pos.y));
    else if (side == RIGHT)
        gl_Position = vec4(rel_pos.y, 0,0, make_nonzero(rel_pos.x));
    else if (side == LEFT)
        gl_Position = vec4(rel_pos.y, 0,0, make_nonzero(-rel_pos.x));
    else // This should never be the case
        gl_Position = vec4(0,0,0,0);
}

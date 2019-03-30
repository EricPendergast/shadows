#version 450

in vec3 rel_pos;
layout(location = 0) out vec4 color_out;

void main (void) {
    float depth = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    color_out = vec4(depth, 0, 0, 1);
    // Depth needs to be small for some reason. Maybe TODO figure out why it
    // needs to be small.
    gl_FragDepth = depth/1000000;
}

#version 450

in vec3 rel_pos;

void main (void) {
    float depth = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    gl_FragData[0] = vec4(depth, 0, 0, 1);
    // Depth needs to be small for some reason. Maybe TODO figure out why it
    // needs to be small.
    gl_FragDepth = depth/1000000;
}

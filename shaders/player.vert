#version 450
uniform mat4 world_to_screen;
uniform vec2 player_pos;
uniform vec2 player_rect;
// How do I pass these to the fragment shader?

layout(location = 0) in vec4 in_pos;

// Assumes coordinates passed in are world
// coordinates.
void main(void) {
    gl_Position = world_to_screen * in_pos;
}

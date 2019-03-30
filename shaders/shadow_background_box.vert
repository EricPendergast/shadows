#version 450
// Maps from world coordinates to screen coordinates, where screen coordinates
// have -1 <= x,y <= 1, w=1
uniform mat4 world_to_screen;

uniform vec2 light_pos;

layout(location = 0) in vec4 in_pos;

noperspective out vec2 rel_pos;

// Assumes coordinates passed in are world coordinates.
void main(void) {
    gl_Position = world_to_screen * in_pos;
    rel_pos = in_pos.xy - light_pos;
}

#version 450
uniform mat4 world_to_screen;

uniform vec2 light_pos;

layout(location = 0) in vec4 in_Position;

noperspective out vec2 rel_pos;

// Assumes coordinates passed in are world coordinates.
void main(void) {
    gl_Position = world_to_screen*in_Position;
    rel_pos = in_Position.xy - light_pos;
}

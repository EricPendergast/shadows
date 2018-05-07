#version 450
// 'mat' takes world coordinates to screen coordinates 
// (x and y in range -1 to 1)
uniform mat4 mat;

uniform vec2 light_pos;

layout(location = 0) in vec4 in_Position;

noperspective out vec2 rel_pos;

// Assumes coordinates passed in are world coordinates.
void main(void) {
    gl_Position = mat*in_Position;
    rel_pos = in_Position.xy - light_pos;
}

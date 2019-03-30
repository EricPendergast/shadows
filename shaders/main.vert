#version 450
uniform mat4 world_to_screen;

layout(location = 0) in vec4 in_pos;

//out vec2 pos;

// Assumes coordinates passed in are world
// coordinates.
void main(void) {
    //pos = vec2(in_pos.x, in_pos.y);
    
    gl_Position = world_to_screen * in_pos;
}

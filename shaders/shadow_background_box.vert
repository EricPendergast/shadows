#version 450
uniform mat4 mat;
/*uniform mat4 proj2;*/

/*uniform vec4 modelview_matrix;*/
/*uniform vec4 projection_matrix;*/

uniform vec2 light_pos;

layout(location = 0) in vec4 in_Position;

/*out vec2 pos;*/
noperspective out vec2 rel_pos;
/*out mat4 mat_out;*/

// Assumes coordinates passed in are world
// coordinates.
void main(void) {
    /*pos = vec2(in_Position.x, in_Position.y);*/

    /*rel_pos = (proj*vec4(pos.x,pos.y,0.0,1.0)).xy;*/

    /*gl_Position = projection_matrix * (modelview_matrix * in_Position);*/
    gl_Position = mat*in_Position;
    rel_pos = in_Position.xy;
    /*rel_pos.y = -250 - rel_pos.y;*/
}

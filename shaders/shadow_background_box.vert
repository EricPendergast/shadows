uniform mat4 proj;

varying vec2 pos;
varying vec2 rel_pos;

// Assumes coordinates passed in are world
// coordinates.
void main(void) {
    pos = vec2(gl_Vertex.x, gl_Vertex.y);
    
    rel_pos = (proj*vec4(pos.x,pos.y,0.0,1.0)).xy;
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}



/*#version 150*/
/*uniform mat4 proj;*/
/**/
/*in vec4 in_Position;*/
/**/
/*out vec2 pos;*/
/*out vec2 rel_pos;*/
/**/
/*// Assumes coordinates passed in are world*/
/*// coordinates.*/
/*void main(void) {*/
/*    pos = vec2(in_Position.x, in_Position.y);*/
/*    */
/*    rel_pos = (proj*vec4(pos.x,pos.y,0.0,1.0)).xy;*/
/*    */
/*    gl_Position = gl_ModelViewProjectionMatrix * in_Position;*/
/*}*/

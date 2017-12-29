varying vec2 pos;
varying vec2 rel_pos;

uniform vec2 light_pos;
// Assumes coordinates passed in are world
// coordinates.
void main(void) {
    pos = vec2(gl_Vertex.x, gl_Vertex.y);
    rel_pos = pos - light_pos;
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

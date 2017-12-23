varying vec2 pos;

// Assumes coordinates passed in are world
// coordinates.
void main(void) {
    pos = vec2(gl_Vertex.x, gl_Vertex.y);
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

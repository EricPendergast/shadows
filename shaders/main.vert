varying vec2 pos;

// Assumes coordinates passed in are world
// coordinates.
void main(void) {
    vec4 a = gl_Vertex;
    
    pos = vec2(gl_Vertex.x, gl_Vertex.y);
    
    gl_Position = gl_ModelViewProjectionMatrix * a;
    
}       

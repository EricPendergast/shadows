varying vec2 pos;

void main(void) {
    vec4 a = gl_Vertex;
    /*a.x = a.x * 0.5;*/
    /*a.y = a.y * 0.5;*/
    
    pos = vec2(gl_Vertex.x, gl_Vertex.y);
    
    gl_Position = gl_ModelViewProjectionMatrix * a;
    
}       

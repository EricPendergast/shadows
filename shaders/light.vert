void main(void) {
    vec4 a = gl_Vertex;
    a.y = -1.0;
    gl_Position = a;
}       

void main(void) {
    vec4 a = gl_Vertex;
    float distance = sqrt(a.x*a.x + a.y*a.y);
    float angle = atan(a.x, a.y)/3.141;
    
    gl_Position = vec4(angle,-1, 0, 1);
}

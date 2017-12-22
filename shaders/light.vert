// Assumes coordinates passed in are world
// coordinates.

varying float distance;

void main(void) {
    vec4 a = gl_Vertex;
    distance = sqrt(a.x*a.x + a.y*a.y);
    float angle = atan(a.y, a.x)/3.141;
    
    gl_Position = vec4(angle, 0, 0, 1);
}

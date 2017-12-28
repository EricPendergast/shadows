// Assumes coordinates passed in are world
// coordinates.

varying float distance;
varying float distanceinv;
varying float distancesq;
varying vec4 position;

void main(void) {
    vec4 a = gl_Vertex;
    position = gl_Vertex;
    distance = pow(sqrt(a.x*a.x + a.y*a.y),1) * pow(sin(atan(position.y,position.x)),1);
    distanceinv = 1.0/pow(sqrt(a.x*a.x + a.y*a.y), 6);
    
    float pi = 3.141592654;
    float angle = atan(a.y, a.x)/pi;
    
    gl_Position = vec4(angle, 0, 0, 1);
}

// Assumes coordinates passed in are world
// coordinates.

varying float distance_atan;

void main(void) {
    // Use atan() because of trig magic. For some reason doing perspective
    // interpolation on atan(distance) gives the right result for fragment
    // distance when fragment position is proportional to that fragment's angle
    // to the light. This was found through trial and error. May not be 100%
    // correct.
    float distance = sqrt(gl_Vertex.x*gl_Vertex.x + gl_Vertex.y*gl_Vertex.y);
    distance_atan = atan(distance);
    
    float pi = 3.141592654;
    float angle = atan(gl_Vertex.y, gl_Vertex.x)/pi;
    
    gl_Position = vec4(angle, 0, distance/5000.0, 1);
}

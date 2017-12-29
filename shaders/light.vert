// Assumes coordinates passed in are world
// coordinates.

varying float distance_atan;
varying float distance;
varying vec4 rel_pos;
uniform vec2 light_pos;

void main(void) {
    float pi = 3.141592654;
    rel_pos = gl_Vertex - vec4(light_pos.x, light_pos.y,0,0);
    // For some reason doing perspective interpolation on atan(distance) gives
    // the (kind of) right result for fragment distance when fragment position
    // is proportional to that fragment's angle to the light. This was found
    // through trial and error.
    distance = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    distance_atan = atan(distance);
    
    float angle = atan(rel_pos.y, rel_pos.x)/pi;
    
    gl_Position = vec4(angle, -.5, distance/5000.0, 1);
}

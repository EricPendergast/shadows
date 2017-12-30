// Assumes coordinates passed in are world
// coordinates.

varying float distance_atan;
varying float distance;
varying float in_range;
varying vec4 rel_pos;
uniform vec2 light_pos;
// Says whether to render polygons on the right side of the light or the left
// side. -1 for left, 1 for right.
uniform float right_or_left;

void main(void) {
    float pi = 3.141592654;
    rel_pos = gl_Vertex - vec4(light_pos.x, light_pos.y,0,0);
    // For some reason doing perspective interpolation on atan(distance) gives
    // the (kind of) right result for fragment distance when fragment position
    // is proportional to that fragment's angle to the light. This was found
    // through trial and error.
    distance = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    distance_atan = atan(distance);

    // Note the negative
    float angle = atan(rel_pos.y, right_or_left*rel_pos.x);

    in_range = 1.0;

    if (abs(angle) > pi/2.0) {
        in_range = 0.0;
    }

    gl_Position = vec4(angle/pi, 0, distance/5000.0, 1);
}

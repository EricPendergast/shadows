#version 150

in float distance_inv;
in float distance;
in float in_range;
in vec4 rel_pos;

// Stores the interpolated distance into the color buffer
void main (void) {
    gl_FragDepth = distance/5000.0;
    /*gl_FragData[0] = vec4(distance, 0, 0, 1);*/
    float dist = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    
    if (in_range > .00001)
        /*gl_FragData[0] = vec4(1.0/sqrt(distance_inv), 0, 0, 1);*/
        gl_FragData[0] = vec4(dist, 0, 0, 1);
    else
        gl_FragData[0] = vec4(1000000, 0, 0, 1);
}

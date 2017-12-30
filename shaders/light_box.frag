varying float distance_atan;
varying float distance;
varying float in_range;
varying vec4 rel_pos;

// Stores the interpolated distance into the color buffer
void main (void) {
    /*gl_FragDepth = tan(distance_atan)/5000.0;*/
    /*gl_FragData[0] = vec4(distance, 0, 0, 1);*/
    
    if (in_range > .00001)
        gl_FragData[0] = vec4(tan(distance_atan), 0, 0, 1);
    else
        gl_FragData[0] = vec4(1000000, 0, 0, 1);
}

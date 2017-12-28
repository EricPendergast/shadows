varying float distance_atan;

// Stores the interpolated distance into the color buffer

void main (void) {
    gl_FragData[0] = vec4(0, tan(distance_atan), 0, 1);
}

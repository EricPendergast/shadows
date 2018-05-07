#version 450

void main (void) {
    // Retrieving the depth.
    // TODO: Figure out why it's off by a factor of 2.
    gl_FragData[0] = vec4(2*gl_FragCoord.z / gl_FragCoord.w, 0, 0, 1);
    
}

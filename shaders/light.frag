varying float distance;

void main (void) {
    // Not sure if there is a difference between interpolating distance, or
    // interpolating the point and calculating the distance of the point. But
    // this seems to work.
    /*float dist = sqrt(position.x*position.x + position.y*position.y);*/
    float dist = distance;
    gl_FragData[0] = vec4(dist, dist, dist, 1);
}

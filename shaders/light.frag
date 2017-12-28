varying float distance;
varying float distancesq;
varying float distanceinv;
varying vec4 position;

void main (void) {
    // Not sure if there is a difference between interpolating distance, or
    // interpolating the point and calculating the distance of the point. But
    // this seems to work.
    /*float dist = sqrt(position.x*position.x + position.y*position.y);*/
    float dist = distance / pow(sin(atan(position.y,position.x)),1);
    /*float dist = pow(1.0/distanceinv, 1.0/6.0) + .1;*/
    // TODO: Writing to depth buffer is slow. Optimize at some point
    gl_FragDepth = dist/5000.0;
    /*gl_FragDepth = .5;*/
    gl_FragData[0] = vec4(dist, dist, dist, 1);
}

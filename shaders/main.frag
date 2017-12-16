uniform sampler2D texture;
// pos is the interpolated world coordinates
varying vec2 pos;

bool in_shadow();

void main (void) {     
    float angle = atan(pos.y, pos.x);
    float tex_lookup = (angle + 3.141)/6.28;
    
    gl_FragColor = texture2D(texture, vec2(tex_lookup, 0.0));
}  

/*bool in_shadow() {*/
/*    float sample = atan(pos.y,pos.x)/6.28;*/
/*    return texture2D(texture, vec2(sample*2.0,0.0)).r == 0.0;*/
/*}*/

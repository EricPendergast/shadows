/*uniform sampler1D texture;*/
uniform sampler2D tex;
// pos is the interpolated world coordinates
varying vec2 pos;

bool in_shadow();

void main(void) {
    float angle = atan(pos.y, pos.x);
    float tex_lookup = (angle + 3.141)/6.28;
    
    /*vec4 looked_up = vec4(0);*/
    vec4 looked_up = texture2D(tex, vec2(tex_lookup,0));
    
    float dist = sqrt(pos.x*pos.x + pos.y*pos.y);
    if (dist < looked_up.g)
        gl_FragColor = vec4(1,1,1,1);
    else
        gl_FragColor = vec4(0,0,0,1);
}  

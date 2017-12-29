uniform sampler2D tex;
// pos is the interpolated world coordinates
varying vec2 pos;
varying vec2 rel_pos;

void main(void) {
    float pi = 3.141592654;
    float angle = atan(rel_pos.y, rel_pos.x);
    float tex_lookup = (angle + pi)/(2.0*pi);
    
    vec4 looked_up = texture2D(tex, vec2(tex_lookup,0));
    
    float dist = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    if (dist < looked_up.x)
        gl_FragColor = vec4(1,1,1,1);
    else
        gl_FragColor = vec4(0,0,0,1);
}  

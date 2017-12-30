uniform sampler2D tex;
// pos is the interpolated world coordinates
varying vec2 pos;
varying vec2 rel_pos;

float get_light_reach(vec2 r_pos);

void main(void) {
    float reach = get_light_reach(rel_pos);
    float dist = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    if (dist < reach)
        gl_FragColor = vec4(1,1,1,1);
    else
        gl_FragColor = vec4(0,0,0,1);
}

float get_light_reach(vec2 r_pos) {
    float pi = 3.141592654;
    float angle = atan(rel_pos.y, abs(rel_pos.x));
    float tex_height_offset = rel_pos.x > 0.0 ? .75 : .25;
    
    float tex_lookup = (angle + pi)/(2.0*pi);
    
    vec4 looked_up = texture2D(tex, vec2(tex_lookup, tex_height_offset));
    
    return looked_up.x;
}

#version 450
uniform sampler2D tex;

// pos is the interpolated world coordinates
/*in vec2 pos;*/
in vec2 rel_pos;


float get_light_reach(vec2 r_pos);

float sign(float v) {
    return  v > 0.0 ? 1.0 : -1.0;
}

float dbg(vec2 r_pos) {
    if (r_pos.x < r_pos.y)
        return 0;
    else 
        return 1000;
    
}

void main(void) {
    float reach = get_light_reach(rel_pos);
    float dist = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    if (dist < reach) {
        gl_FragColor = vec4(1,1,1,1);
    } else
        gl_FragColor = vec4(0,0,0,1);
}


float get_light_reach(vec2 r_pos) {
    float shift = .25;
    if (abs(r_pos.y) > abs(r_pos.x)) {
        float tmp = r_pos.y;
        r_pos.y = r_pos.x;
        r_pos.x = tmp;
        shift = .75;
    }
    // plane_proj is in the range from -1 to 1
    float plane_proj = r_pos.y / abs(r_pos.x);

    float tex_x = plane_proj/2.0 + .5;
    // Prevents texture lookup from wrapping
    tex_x = clamp(tex_x, .0001, .9999);
    vec4 looked_up = texture2D(tex, vec2(tex_x, shift + .125*sign(r_pos.x)));

    return looked_up.x;
}
// horizontal planes
/*float get_light_reach(vec2 r_pos) {*/
/*    // plane_proj is in the range from -1 to 1*/
/*    float plane_proj = r_pos.x / abs(r_pos.y);*/
/*    if (abs(plane_proj) > 1.0)*/
/*        return 1000000.0;*/
/**/
/*    vec4 looked_up = texture2D(tex, vec2(plane_proj/2.0 + .5, .75 + .125*sign(r_pos.y)));*/
/**/
/*    return looked_up.x;*/
/*}*/

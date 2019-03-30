#version 450

uniform sampler2D tex;
uniform vec2 light_pos;

in vec2 rel_pos;
layout(location = 0) out vec4 color_out;


float get_light_reach(vec2 r_pos);

float sign(float v) {
    return  v > 0.0 ? 1.0 : -1.0;
}

void main(void) {
    float reach = get_light_reach(rel_pos);
    float dist = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    if (dist < reach) {
        color_out = vec4(1,1,1,1);
    } else
        color_out = vec4(0,0,0,1);
    
}


float get_light_reach(vec2 r_pos) {
    float shift = .25;
    if (abs(r_pos.x) > abs(r_pos.y)) {
        float tmp = r_pos.y;
        r_pos.y = r_pos.x;
        r_pos.x = tmp;
        shift = .75;
    }
    // plane_proj is in the range from -1 to 1
    float plane_proj = r_pos.x / abs(r_pos.y);

    float tex_x = plane_proj/2.0 + .5;
    vec4 looked_up = texture2D(tex, vec2(tex_x, shift - .125*sign(r_pos.y)));

    return looked_up.x;
}

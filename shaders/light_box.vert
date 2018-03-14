#version 450
// Assumes coordinates passed in are world
// coordinates.

uniform mat4 proj;
uniform vec2 light_pos;
// Says whether to render polygons onto the horizontal projection planes or the
// vertical ones side. -1 for horizontal, 1 for vertical.
uniform float horiz_or_vert;

layout(location = 0) in vec4 in_Position;

out float distance_inv;
out float distance;
out float in_range;
out vec4 rel_pos;

float sign(float v) {
    return  v > 0.0 ? 1.0 : -1.0;
}


void main(void) {
    /*if (proj * vec4()*/
    /*rel_pos = gl_Vertex - vec4(light_pos.x, light_pos.y,0,0);*/
    /*rel_pos = gl_Vertex - vec4(proj[0][0], proj[0][1],0,0);*/
    rel_pos = proj * in_Position;
    /*if (horiz_or_vert < 0.0) { //if horiz_or_vert == -1*/
    /*    float tmp = rel_pos.x;*/
    /*    rel_pos.x = rel_pos.y;*/
    /*    rel_pos.y = tmp;*/
    /*}*/
    distance = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
    distance_inv = 1.0/(distance*distance);

    in_range = 1.0;
    
    float plane_proj = rel_pos.x / abs(rel_pos.y);

    gl_Position = vec4(plane_proj, .5*sign(rel_pos.y), 0, 1);
}

// Horizontal
/*void main(void) {*/
/*    rel_pos = gl_Vertex - vec4(light_pos.x, light_pos.y,0,0);*/
/*    // For some reason doing perspective interpolation on atan(distance) gives*/
/*    // the (kind of) right result for fragment distance when fragment position*/
/*    // is proportional to that fragment's angle to the light. This was found*/
/*    // through trial and error.*/
/*    distance = 1.0/sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);*/
/*    distance_atan = atan(distance);*/
/**/
/*    in_range = 1.0;*/
/*    */
/*    float plane_proj = rel_pos.x / abs(rel_pos.y);*/
/**/
/*    gl_Position = vec4(plane_proj, .5*sign(rel_pos.y), 1.0/distance/5000.0, 1);*/
/*}*/

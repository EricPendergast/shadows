#version 450
// Assumes coordinates passed in are world
// coordinates.

uniform vec2 light_pos;


// Says which side of the projection square to project onto
uniform int side;

uniform int UP = 0;
uniform int DOWN = 1;
uniform int RIGHT = 2;
uniform int LEFT = 3;

layout(location = 0) in vec4 in_Position;

float sign(float v) {
    return  v > 0.0 ? 1.0 : -1.0;
}

void main(void) {
    /*vec2 rel_pos = in_Position.xy - vec2(500,500);*/
    vec2 rel_pos = in_Position.xy - light_pos;
    
    
    if (side == UP)
        gl_Position = vec4(rel_pos.x, 0, rel_pos.x, rel_pos.y);
    else if (side == DOWN)
        gl_Position = vec4(rel_pos.x, 0, rel_pos.x, -rel_pos.y);
    else if (side == RIGHT)
        gl_Position = vec4(-rel_pos.y, 0, -rel_pos.y, rel_pos.x);
    else if (side == LEFT)
        gl_Position = vec4(rel_pos.y, 0, rel_pos.y, -rel_pos.x);
    else
        gl_Position = vec4(0,0,0,0);
}

//void main(void) {
//    /*if (proj * vec4()*/
//    /*rel_pos = gl_Vertex - vec4(light_pos.x, light_pos.y,0,0);*/
//    /*rel_pos = gl_Vertex - vec4(proj[0][0], proj[0][1],0,0);*/
//    rel_pos = proj * in_Position;
//    /*if (horiz_or_vert < 0.0) { //if horiz_or_vert == -1*/
//    /*    float tmp = rel_pos.x;*/
//    /*    rel_pos.x = rel_pos.y;*/
//    /*    rel_pos.y = tmp;*/
//    /*}*/
//    distance = sqrt(rel_pos.x*rel_pos.x + rel_pos.y*rel_pos.y);
//    distance_inv = 1.0/(distance*distance);
//
//    in_range = 1.0;
//    
//    float plane_proj = rel_pos.x / abs(rel_pos.y);
//
//    gl_Position = vec4(plane_proj, .5*sign(rel_pos.y), 0, 1);
//}

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

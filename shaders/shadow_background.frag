uniform sampler2D texture;
varying vec2 pos;

bool in_shadow();

void main (void) {     
    /*float val = atan(pos.x,pos.y)/6.28*500.0;*/
    
    // put it in the range from zero to
    // one
    
    /*gl_FragColor = vec4(val,val,val,1);*/
    gl_FragColor = (texture2D(texture, vec2(pos.x/500.0,0.0)));
    /*gl_FragColor = vec4(val01,val01,val01,1);*/
    
    /*gl_FragColor = vec4(in_shadow(), 1.0,1.0,1.0);//shadow*/
    /*gl_FragColor = (texture2D(texture, vec2(val01*2.0,0.0)));*/
}  


bool in_shadow() {
    float sample = atan(pos.x,pos.y)/6.28;
    return texture2D(texture, vec2(sample*2.0,0.0)).r == 0.0;
}

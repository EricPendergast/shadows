uniform sampler2D texture;
varying vec2 pos;

void main (void) {     
    /*gl_FragColor = vec4(pos.x/500.0, 1.0, 1.0, 1.0);*/
    /*gl_FragColor = (texture2D(texture, vec2(pos.x/150.0,0.0)));*/
    /*if (pos.x > 250.0)*/
    /*    gl_FragColor = vec4(.5, .5, 0.0, 1.0);*/
    /*else*/
    /*gl_FragColor = vec4(1.0, .5, 0.0, 1.0);*/
    int thing = int(gl_FragCoord.x);
    /*if (thing == 10 || thing == 11) {*/
        /*if (thing == 10)*/
        /*    thing = 11;*/
        /*else if (thing == 11)*/
        /*    thing = 11;*/
        gl_FragColor = (texture2D(texture, vec2(thing/500.0,0.0)));
    /*}*/
    /*else */
        /*gl_FragColor = vec4(0.0, float(thing)/500.0, 0.0, 1.0);*/
    /*gl_FragColor = (texture2D(texture, vec2(thing,0.0)));*/
}  

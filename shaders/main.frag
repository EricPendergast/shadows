uniform sampler2D texture;
varying vec2 pos;

void main (void) {     
    int thing = int(gl_FragCoord.x);
    gl_FragColor = (texture2D(texture, vec2(thing/500.0,0.0)));
}  

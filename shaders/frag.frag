uniform sampler2D texture;

void main (void) {     
    gl_FragColor = (texture2D(texture, vec2(0,0)));
}  

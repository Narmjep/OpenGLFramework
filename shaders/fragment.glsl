in vec3 colorF;

uniform vec2 resolution;

void main(){
    float x = gl_FragCoord.y/resolution.y;
    x = abs(sin(x));
    vec3 newColor = vec3(x);
    gl_FragColor = vec4(newColor,1.0);
}
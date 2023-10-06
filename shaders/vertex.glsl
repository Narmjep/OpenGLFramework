layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 colorV;
layout(location = 2) in vec2 texturePosV;

out vec3 colorF;
out vec2 texturePosF;

void main(){
    gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
    colorF = colorV;
    texturePosF = texturePosV;
}
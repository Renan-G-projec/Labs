// Ad Maiorem Dei Gloriam!
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

uniform mat4 uModel;
uniform mat4 uCamera;

out vec3 iPosition;
flat out vec3 iNormal;
out vec2 iUV;

void main() {
    gl_Position = uCamera * uModel * vec4(aPos, 1.0);
    iPosition = (uModel * vec4(aPos, 1)).xyz;
    iNormal = aNorm;
    iUV = aUV;
}

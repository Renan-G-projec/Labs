// Ad Maiorem Dei Gloriam!
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

uniform mat4 uMVP;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

void main() {
    gl_Position = uMVP * vec4(aPos, 1.0);
    Position = aPos;
    Normal = aNorm;
    UV = aUV;
}

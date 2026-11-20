// Ad Maiorem Dei Gloriam!
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec4 aModelMatrixColumn0;
layout (location = 4) in vec4 aModelMatrixColumn1;
layout (location = 5) in vec4 aModelMatrixColumn2;
layout (location = 6) in vec4 aModelMatrixColumn3;

uniform mat4 uCamera;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

void main() {
    mat4 model = mat4(aModelMatrixColumn0, aModelMatrixColumn1, aModelMatrixColumn2, aModelMatrixColumn3);

    gl_Position = uCamera * model * vec4(aPos, 1.0);
    Position = (model * vec4(aPos, 1)).xyz;
    Normal = mat3(model) * aNorm;
    UV = aUV;
}

// Ad Maiorem Dei Gloriam!
#version 460 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

out vec4 FragColor;

uniform sampler2D uTex;

uniform vec3 ambientLight;
uniform vec3 lightPos;

void main() {
    
    vec3 lightDir = normalize(lightPos - Position);
    vec3 normal = normalize(Normal);

    vec4 ambient = vec4(ambientLight, 1.0);
    float diffuse = max(dot(normal, lightDir), 0.0);

    FragColor = texture(uTex, UV) * (ambient + diffuse);
}

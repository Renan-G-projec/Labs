// Ad Maiorem Dei Gloriam!
#version 460 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

out vec4 FragColor;

uniform sampler2D uTex;

uniform vec3 ambientLight;
uniform vec3 lightPos;
uniform vec3 viewerPos;
uniform float specularFactor;

void main() {
    
    vec3 lightDir = normalize(lightPos - Position);
    vec3 normal = normalize(Normal);
    vec3 viewerDir = normalize(viewerPos - Position);

    vec3 ambient = ambientLight;
    vec3 diffuse = vec3(max(dot(normal, lightDir), 0.0));
    vec3 specular = vec3(pow(max(dot(reflect(-lightDir, normal), viewerDir), 0.0), specularFactor));

    FragColor = texture(uTex, UV) * vec4(ambient + diffuse + specular, 1.0);
}

// Ad Maiorem Dei Gloriam!
#version 460 core
#define MAX_LIGHTS 4

in vec3 iPosition;
in vec3 iNormal;
in vec2 iUV;

out vec4 FragColor;

uniform sampler2D uTex;


// MATERIAL
struct Material
{

// AMBIENT
    float specularIntensity;
    float shineness;
};
uniform Material uMaterial;

// AMBIENT
uniform vec3 uAmbientLightColor;
uniform float uAmbientLightIntensity;

// DIRECTIONAL
struct DirectionalLight
{
    vec3 direction;
    vec3 color;
    float intensity;
};
uniform DirectionalLight uDirectionalLight;

// POINT
struct PointLight
{
    vec3 color;
    vec3 position;
    float ambient_intensity;
    float intensity;
    float quadratic;
    float linear;
    float constant;
};
uniform PointLight uPointLight;

uniform vec3 viewerPos;

float calculate_attenuation(float _distance, float _linear, float _quadratic, float _constant)
{
    return 1.0 / (_quadratic * pow(_distance, 2) + _linear * _distance + _constant);
}

vec3 calculate_point_lights() 
{
    vec3 toLight = uPointLight.position - iPosition;
    vec3 directionToLight = normalize(toLight);
    vec3 normal = normalize(iNormal);
    vec3 viewerDir = normalize(viewerPos - iPosition);

    float attenuation = calculate_attenuation(length(toLight), uPointLight.linear, uPointLight.quadratic, uPointLight.constant);
    float ambient = uPointLight.ambient_intensity;
    float diffuse = max(dot(normal, directionToLight), 0.0);
    float specular = diffuse <= 0 ? 0.0 : uMaterial.specularIntensity * pow(max(dot(reflect(-directionToLight, normal), viewerDir), 0.0), uMaterial.shineness);

    float light = (ambient + diffuse + specular) * uPointLight.intensity * attenuation;

    return uPointLight.color * light;
}

void main() 
{
    
    vec3 lightDir = normalize(-uDirectionalLight.direction);
    vec3 normal = normalize(iNormal);
    vec3 viewerDir = normalize(viewerPos - iPosition);

    float diffuseFactor = max(0.0, dot(normal, lightDir));

    vec3 ambient = uAmbientLightColor * uAmbientLightIntensity;
    vec3 diffuse = uDirectionalLight.color * uDirectionalLight.intensity * max(diffuseFactor, 0.0);
    vec3 specular = vec3(0.0);
    if (diffuseFactor > 0)
    {
        specular = uDirectionalLight.color * uDirectionalLight.intensity * uMaterial.specularIntensity * pow(max(dot(reflect(-lightDir, normal), viewerDir), 0.0), uMaterial.shineness);
    }

    vec3 light = ambient + diffuse + specular;
    vec3 pointlight = calculate_point_lights();
    FragColor = texture(uTex, iUV) * vec4(light + pointlight, 1.0);
}

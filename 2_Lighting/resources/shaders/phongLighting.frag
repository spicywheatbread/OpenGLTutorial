#version 330 core
out vec4 FragColor;
  
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform Light light;
uniform Material material;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos);
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // Important vars
    vec3 norm = normalize(Normal);
    
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // Ambient Component
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    // Diffuse Component
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    // Specular Component
    vec3 viewDir = normalize(vec3(0, 0, 0) - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    diffuse  *= intensity;
    specular *= intensity;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}


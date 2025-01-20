#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec3 color;

float specularStrength = 0.5;

// In Gouraud Shading, we perform lighting calculations in the vertex shader instead of the fragment shader.
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vec3 position = vec3(view * model * vec4(aPos, 1.0));
    
    // Calculate the normal matrix so that non-uniform scaling doesn't mess up our normal
    mat3 normalMatrix = mat3(transpose(inverse(view * model))); // Inversing matrices is expensive for shaders, typically do on CPU.
    
    // Reused variables
    vec3 norm = normalize(normalMatrix * aNormal);
    vec3 lightDir = normalize(lightPos - vec3(position));
    
    // Ambient Component
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse Component
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular Component
    vec3 viewDir = normalize(vec3(0, 0, 0) - vec3(position));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    color = (ambient + diffuse + specular) * objectColor;
}

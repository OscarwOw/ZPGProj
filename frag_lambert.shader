#version 330 core
in vec3 fragColor;
in vec3 Normal;
in vec3 FragPos; 
in vec3 lightPos;
in vec3 cameraPos;

layout(location = 0) out vec4 frag_colour;

void main() {
    const vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float specularStrength = 0.5;

    // Normalize vectors
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(cameraPos - FragPos);

    // Diffuse component
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Blinn-Phong specular component
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32); // Shininess exponent
    vec3 specular = specularStrength * spec * lightColor;

    // Ambient component
    vec3 ambient = 0.1 * lightColor;

    // Combine results and apply fragment color
    vec3 result = (ambient + diffuse + specular) * fragColor;
    frag_colour = vec4(result, 1.0);
}

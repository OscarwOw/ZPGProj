#version 330 core
in vec3 fragColor; 
in vec3 Normal;
in vec3 FragPos; 
in vec3 cameraPos;
in vec3 lightPos;
in vec3 fragNormal;

layout(location = 0) out vec4 frag_colour;
void main() {
    const vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float specularStrength = 0.5;
    vec3 normal = normalize(fragNormal);

    vec3 lightDir = normalize(lightPos - FragPos);
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 ambient = 0.1 * lightColor;
    vec3 result = (ambient + diffuse + specular) * fragColor; 
    //difuse vynasobit s materialom
    //specular vynasobit s materialom
    //a nasledne spocitat

    frag_colour = vec4(result, 1.0);
};
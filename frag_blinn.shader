in vec3 fragColor; 
in vec3 Normal; 
in vec3 FragPos;
in vec3 lightPos;

layout(location = 0) out vec4 frag_colour;
void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0);
    
    vec3 result = (ambient + diffuse) * fragColor;

    frag_colour = vec4(result, 1.0);
};
in vec3 fragColor; 
in vec3 Normal;
in vec3 FragPos; 
uniform vec3 lightPosition;

layout(location = 0) out vec4 frag_colour;
void main() {
    const vec3 lightColor = vec3(1.0, 1.0, 1.0);
    
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    vec3 ambient = 0.1 * lightColor;
    vec3 result = (ambient + diffuse) * fragColor;

    frag_colour = vec4(result, 1.0);
};
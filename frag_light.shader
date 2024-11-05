in vec3 fragColor; 
in vec3 Normal;
in vec3 FragPos; 
in vec3 cameraPos;
in vec3 lightPos;
in vec3 fragNormal;

layout(location = 0) out vec4 frag_colour;
void main() {

    vec3 result =  fragColor;

    frag_colour = vec4(result, 1.0);
};
#version 330 core
in vec3 fragColor; 
in vec3 Normal;
in vec3 FragPos; 
in vec3 cameraPos;
in vec3 lightPos;
in vec3 fragNormal;

uniform int numLights; // Number of light sources

struct Light {
    vec3 position;
    vec3 color;
};

uniform Light lightSources[10];

uniform vec3 materialAmbient;    // Ambient reflectivity (r_a)
uniform vec3 materialDiffuse;    // Diffuse reflectivity (r_d)
uniform vec3 materialSpecular;   // Specular reflectivity (r_s)
uniform float materialShininess; // Shininess factor (s)

const vec3 SpecularlightColor = vec3(0.7, 0.7, 0.7);
const vec3 DifuselightColor = vec3(0.5, 0.2, 0.2);
const vec3 AmbientlightColor = vec3(0.1, 0.1, 0.1);

layout(location = 0) out vec4 frag_colour;

void main() {
    vec3 result = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(cameraPos - FragPos);


    for(int i=0; i< numLights;i++){
        vec3 lightPos = lightSources[i].position;
        vec3 lightColor = lightSources[i].color;

        //ambient component
        vec3 ambient = materialAmbient * AmbientlightColor;

        //diffuse component
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * DifuselightColor * materialDiffuse;

        //specular component
        vec3 reflectDir = reflect(-lightDir, normal);
    
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
        vec3 specular = materialSpecular * spec * SpecularlightColor;  

        //combine components
        result += ambient + diffuse + specular;
    }

    result *= fragColor;
    frag_colour = vec4(result, 1.0);  
};
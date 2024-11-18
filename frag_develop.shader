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
    vec3 direction;
    int lightType;
    float angle;
    float intensity;
};

uniform Light lightSources[50];

uniform vec3 materialAmbient;    // Ambient reflectivity (r_a)
uniform vec3 materialDiffuse;    // Diffuse reflectivity (r_d)
uniform vec3 materialSpecular;   // Specular reflectivity (r_s)
uniform float materialShininess; // Shininess factor (s)

const vec3 SpecularlightColor = vec3(0.7, 0.7, 0.7);
const vec3 DifuselightColor = vec3(0.5, 0.2, 0.2);
const vec3 AmbientlightColor = vec3(0.1, 0.1, 0.1);

layout(location = 0) out vec4 frag_colour;



vec3 calculatePointLight(Light light, vec3 normal, vec3 viewDir) {
    vec3 lightPos = light.position;
    vec3 lightColor = light.color;

    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.018 * (distance * distance));

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

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;


    //combine components
    return ambient + diffuse + specular;
}


vec3 calculateSpotLight(Light light, vec3 normal, vec3 viewDir) {
    vec3 lightPos = light.position;
    vec3 lightColor = light.color;

    vec3 lightDir = normalize(lightPos - FragPos);

    float alpha = dot(light.direction, -lightDir);
    //float epsilon = cos(radians(light.angle));
    if(alpha > light.angle){

        float distance = length(lightPos - FragPos);
        float attenuation = 1.0 / (1.0 + 0.04 * distance + 0.0008 * (distance * distance));

        //ambient component
        vec3 ambient = materialAmbient * AmbientlightColor;

        //diffuse component

        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * DifuselightColor * materialDiffuse;

        //specular component
        vec3 reflectDir = reflect(-lightDir, normal);
    
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
        vec3 specular = materialSpecular * spec * SpecularlightColor;  

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;


        //combine components
        return ambient + diffuse + specular;
    }
    return vec3(0, 0, 0);
}

vec3 calculateDirectionalLight(Light light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    vec3 ambient = materialAmbient * light.color;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * materialDiffuse * light.color * light.intensity;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = materialSpecular * spec * light.color * light.intensity;

    return  ambient + diffuse + specular;
}



void main() {
    vec3 result = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(cameraPos - FragPos);


    for(int i=0; i< numLights;i++){
        if (lightSources[i].lightType == 1) { 
            result += calculatePointLight(lightSources[i], normal, viewDir);
        } 
        else if (lightSources[i].lightType == 2) { // SPOTLIGHT
            result += calculateSpotLight(lightSources[i], normal, viewDir);
        }
        else if (lightSources[i].lightType == 3) { // DIRECTIONAL LIGHT
            result += calculateDirectionalLight(lightSources[i], normal, viewDir);
        } 
    }

    result *= fragColor;
    frag_colour = vec4(result, 1.0);  
};


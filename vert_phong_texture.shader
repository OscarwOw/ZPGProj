#version 330 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 objectColor;

out vec3 fragColor;
out vec3 Normal;
out vec3 FragPos;
out vec3 cameraPos;
out vec3 lightPos;
out vec3 fragNormal;
out vec2 uv_out;

void main() {
    
    vec4 worldPosition = modelMatrix * vec4(vp, 1.0);
    FragPos = vec3(worldPosition);

    fragNormal = mat3(transpose(inverse(modelMatrix))) * color;
    
    
    gl_Position =   projectionMatrix * viewMatrix * worldPosition;
    
    fragColor = objectColor;

    Normal = color;
    cameraPos = cameraPosition;
    lightPos = lightPosition;
    uv_out = uv;
};
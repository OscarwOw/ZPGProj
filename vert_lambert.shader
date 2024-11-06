#version 330 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

out vec3 fragColor;
out vec3 Normal;
out vec3 FragPos;
out vec3 lightPos;
out vec3 cameraPos;


void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    
    fragColor = vec3(0.01, 0.19, 0.12);
    FragPos = vec3(modelMatrix * vec4(vp, 1.0));
    Normal = mat3(transpose(inverse(modelMatrix))) * color; // Transformed normal
    lightPos = lightPosition;
    cameraPos = cameraPosition;
}

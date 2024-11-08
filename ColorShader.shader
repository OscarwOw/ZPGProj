#shader vertex
#version 330
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragColor;
void main() {

    //gl_Position =   u_Perspective * u_ViewMatrix * modelMatrix * vec4(vp, 1.0);
    gl_Position =   projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);


    fragColor = color;
};



#shader fragment
#version 330
in vec3 fragColor; 

layout(location = 0) out vec4 frag_colour;
void main() {
    frag_colour = vec4(fragColor, 1.0);
};

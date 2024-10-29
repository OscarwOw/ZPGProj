#shader vertex
#version 330
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 color;

uniform mat4 u_TransformationMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_Perspective;

out vec3 fragColor;
void main() {


    //gl_Position = u_ViewMatrix * u_TransformationMatrix * vec4(vp, 1.0);
    //gl_Position =  u_TransformationMatrix * vec4(vp, 1.0);
    gl_Position =   u_Perspective * u_ViewMatrix * u_TransformationMatrix * vec4(vp, 1.0);


    fragColor = color;
};



#shader fragment
#version 330
in vec3 fragColor; 

layout(location = 0) out vec4 frag_colour;
void main() {
    frag_colour = vec4(fragColor, 1.0);
};

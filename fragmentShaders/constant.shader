in vec3 fragColor; 

layout(location = 0) out vec4 frag_colour;
void main() {
    frag_colour = vec4(fragColor, 1.0);
};
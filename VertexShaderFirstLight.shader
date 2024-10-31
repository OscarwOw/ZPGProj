layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat3 normalMatrix; //(M-1)T
void main(void){
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp,1.0f);
    ex_worldPosition = modelMatrix * vec4(vp,1.0f);
    //ex_worldNormal = normalMatrix * in_Normal; //pøíštì
}
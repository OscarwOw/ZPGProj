uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix; //(M-1)T
void main(void){
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(in_Position,1.0f);
    ex_worldPosition = modelMatrix * vec4(in_Position,1.0f);
    ex_worldNormal = normalMatrix * in_Normal; //pøíštì
}
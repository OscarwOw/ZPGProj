in vec4 ex_worldPosition;

in vec3 ex_worldNormal;
out vec4 out_Color;
void main(void){
    vec3 lightPosition= vec3(10.0,10.0,10.0); //správnì upravit
    …
    float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + diffuse;
}
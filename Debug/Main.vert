#version 400  core
 
in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projection;

void main(void){
colorOut = colorIn;



gl_Position = projection * viewMatrix * modelMatrix * vec4(vertexIn, 1.0);
}

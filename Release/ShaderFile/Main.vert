#version 400  core
 

in vec3 vertexIn;
out vec3 vertexOut;
in vec3 colorIn;
out vec3 colorOut;
in vec2 textureIn;

in vec3 normalIn;
uniform mat3 normalMatrix;
out vec3 normalOut;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projection;
uniform bool isLit;
out vec2 textureOut;


void SetVarables(){
	colorOut = colorIn;
	vertexOut =  (modelMatrix * vec4(vertexIn, 1.0)).xyz;
	textureOut = textureIn;
	gl_Position = projection * viewMatrix * modelMatrix * vec4(vertexIn, 1.0);
	normalOut = normalMatrix * normalIn;

}



void main(void){
	SetVarables();
}

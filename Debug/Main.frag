#version 400 core

in vec3 colorOut;
out vec4 pixelColor;
uniform float time;

void main(void){


pixelColor = vec4(colorOut, 1.0);


}
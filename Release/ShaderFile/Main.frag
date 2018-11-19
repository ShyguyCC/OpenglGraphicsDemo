#version 400 core


struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float attConstant;
	float attLinear;
	float attQuadratic;
};

uniform Light light;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;
uniform vec3 cameraPosition;
uniform sampler2D textureImage;
uniform bool isTexturedout;
uniform bool isLitfrag;
uniform vec3 lightColor;
in vec3 normalOut;
in vec3 colorOut;
in vec2 textureOut;
in vec3 vertexOut;
out vec4 pixelColor;

//this is when we are lighting a nontextured object.
vec4 LitBlank(){

	vec3 ambientColor = light.ambient * material.ambient;


	vec3 normal = normalize(normalOut);
	vec3 lightDirection = normalize(light.position - vertexOut);
	float lightIntensity = max(dot(lightDirection, normal), 0.0);
	vec3 diffuseColor = light.diffuse * material.diffuse * lightIntensity;


	vec3 viewDirection = normalize(cameraPosition - vertexOut);
	vec3 reflection = reflect(-lightDirection, normal);
	
	
	float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);  
	



	vec3 specularColor = light.specular * material.specular * specularTerm;


	float lightDistance = length(light.position - vertexOut);
	float attenuation = 1.0 / (light.attConstant +	light.attLinear * lightDistance + light.attQuadratic * (lightDistance * lightDistance));
	pixelColor = vec4(((ambientColor + diffuseColor + specularColor) * attenuation),1.0);
//	pixelColor = vec4(((ambientColor + diffuseColor) * attenuation), 1.0);

	return pixelColor;
}
//this is for when we are only textureing the object.
void TextureOnly(){
	if(isLitfrag){
		pixelColor = texture(textureImage, textureOut) * LitBlank();
	}else{		
		pixelColor = vec4(colorOut, 1.0) * texture(textureImage, textureOut);
	}
}

void ColorOnly(){
	pixelColor = vec4(colorOut, 1.0);
}


void TestingTexture(){
    float lum = length(texture2D(textureImage, textureOut).rgb);
     
    pixelColor = vec4(1.0, 1.0, 1.0, 1.0);
     
    if (lum < 1.00) {
        if (mod(gl_FragCoord.x + gl_FragCoord.y, 10.0) == 0.0) {
            pixelColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
    }
     
    if (lum < 0.75) {
        if (mod(gl_FragCoord.x - gl_FragCoord.y, 10.0) == 0.0) {
            pixelColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
    }
     
    if (lum < 0.50) {
        if (mod(gl_FragCoord.x + gl_FragCoord.y - 5.0, 10.0) == 0.0) {
            pixelColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
    }
     
    if (lum < 0.3) {
        if (mod(gl_FragCoord.x - gl_FragCoord.y - 5.0, 10.0) == 0.0) {
            pixelColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
    }
}

uniform bool testFun;
uniform bool testFunTwo;


#define PI 3.14159

uniform float time;

uniform vec2 resolution;

float stroke(float x, float s, float w) {
    float d = step( s, x + w * 0.5 ) - step( s, x - w * 0.5 );
    return clamp( d, 0.0, 1.0 );
}

//i dont know why its taking up half the quad instead of the full quad like it should do.
void FakeWaterFalling() {
    vec3 color = vec3( 0.0 );
    vec2 st = vec2((vertexOut.xy) * 4 / (1024, 768) * 40);
    float offset = cos( ( st.y + time ) * PI ) * 0.15;
    color += stroke( st.x, 0.28 + offset + 0.1 * cos( st.x * 40.0 + time ), 0.1 + 0.05 * cos( time * 2.0 ) );
    color += stroke( st.x, 0.5 + offset + 0.1 * cos( st.x * 40.0 + time ), 0.1 + 0.05 * sin( 0.25 + time * -3.0 ) );
    color += stroke( st.x, 0.72 + offset + 0.1 * cos( st.x * 40.0 + time ), 0.1 + 0.05 * cos( 0.5 + time * 2.5 ) );
    pixelColor = vec4( vec3( color ), 1.0 );
}


void LoadFrag(){
	if(isLitfrag){
		if(isTexturedout){
			TextureOnly();
		} //if text close
		else{
			LitBlank();
		} //else text close
	} //if lit close
	else{
		if(isTexturedout){ //if text close
			TextureOnly();
		}else{ //if text close	
			ColorOnly();
		}// close close
	}
	if(testFun){
		FakeWaterFalling();
	}
	if(testFunTwo){
		TestingTexture();
	}
}





void main(void){
	LoadFrag();
}


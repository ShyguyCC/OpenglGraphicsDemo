#include "TextureClass.h"



TextureClass::TextureClass(){
	std::vector<std::string> facestemp;
	{
		"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"back.jpg",
			"front.jpg";
	};
	faces = facestemp;
}


TextureClass::~TextureClass(){

}




void TextureClass::loadTexture(){

	glGenTextures(1, &textureID);

	SDL_Surface* textureData = 0;
	textureData = IMG_Load("Textures\\Crate.jpg");
	if (!textureData){
		std::cout << "theres been an error, cant open that file" << std::endl;
	}
	//bind
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	unsigned char* pixels = (unsigned char*)textureData->pixels;
	unsigned int width = textureData->w;
	unsigned int height = textureData->h;
	unsigned int depth = textureData->format->BytesPerPixel;
	unsigned int format = ((depth == 4) ? GL_RGBA : GL_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	SDL_FreeSurface(textureData);

	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind
	glBindTexture(GL_TEXTURE_2D, 0);

}

void TextureClass::loadSkyBox(){
	char *CubeMapTextureFiles[6] = { "CubeMapTex\\right.jpg", "CubeMapTex\\left.jpg", "CubeMapTex\\top.jpg", "CubeMapTex\\bottom.jpg", "CubeMapTex\\front.jpg", "CubeMapTex\\back.jpg" };


}

void TextureClass::loadTexture(std::string texturefile){
	glGenTextures(1, &textureID);

	SDL_Surface* textureData = 0;
	const char * CharTextFile = texturefile.c_str();

	textureData = IMG_Load(CharTextFile);
	if (!textureData) {
		std::cout << "theres been an error, cant open that file" << std::endl;
	}
	//bind
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	unsigned char* pixels = (unsigned char*)textureData->pixels;
	unsigned int width = textureData->w;
	unsigned int height = textureData->h;
	unsigned int depth = textureData->format->BytesPerPixel;
	unsigned int format = ((depth == 4) ? GL_RGBA : GL_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	SDL_FreeSurface(textureData);

	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind
	glBindTexture(GL_TEXTURE_2D, 0);

}

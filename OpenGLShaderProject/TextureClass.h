#pragma once
#include <iostream>
#include <glew.h>
#include <SDL_image.h>
#include <vector>



class TextureClass
{
public:
	TextureClass();
	~TextureClass();

	void loadTexture();
	void loadSkyBox();
	void loadTexture(std::string texturefile);


	GLuint getTextID() { return textureID; };

private:
	std::vector<std::string> faces;
	GLuint textureID;
};


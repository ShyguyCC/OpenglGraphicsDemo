#pragma once

#include "TextureClass.h"
#include "MathsClass.h"
#include "ShaderManager.h"
#include "InputManager.h"

//sorry i just couldnt get the text to work. i knew how to cut them out but then to render them was a differnet story.
class TextClass
{
public:
	TextClass();
	~TextClass();
	//this function loads and find the uv for "hello" in the font provided, but it doesnt set it to draw as i didnt get that far.
	void LoadText();
	void DrawText();
private:
	glm::vec2 cellDimension;
	std::string text;
	int textureIndex;
	glm::vec2 textureCell;
	TextureClass TheTexture;
	GLuint offset;
	GLuint offsetText;
	GLuint VAO;
	GLuint vertexVBO;
	GLuint colorVBO;
	GLuint textureVBO;
	GLuint modelMatrixID;
	glm::mat4 BlankMatrix;
	int Scale = 0;
	float DrawingFloat;
	GLuint textureBool;
	GLuint islitBoolFrag;
	GLuint lightBool;
};


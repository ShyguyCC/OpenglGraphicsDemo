#pragma once

#include <iostream>
#include "ShaderManager.h"
#include <glew.h>



class GridClass
{
public:
	GridClass();
	~GridClass();

public:

	void CreateGrid();
	void CreateGrid(float GridSize);
	void DrawGrid();
	void DrawCustomeGrid();

private:
	float GridSizeSave;

	GLuint textureBool;
	GLuint lightBool;
	GLuint islitBoolFrag;

	GLuint modelMatrixID;

	glm::mat4 BlankMatrix;

	float GridSizeSaveDraw;
	GLuint offset;
	GLuint VAO;
	GLuint vertexVBO;
	GLuint colorVBO;



};


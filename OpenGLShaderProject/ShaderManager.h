#pragma once

#include <iostream>
#include <glew.h>
#include <SDL.h>
#include <fstream>
#include <string>
#include "Singleton.h"
#include "InputManager.h"
#include "MathsClass.h"

class ShaderManager
{

	
public:
	ShaderManager();
	~ShaderManager();

	bool CreateProgram();
	bool CreateShaders();

	bool CompileShaders();
	void AttachShaders();
	bool LinkProgram();

	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();

	void CreateBuffer(GLuint Buffer);
	void DestroyBuffer(GLuint Buffer);
	void CreateVertArray(GLuint Buffer);
	void DestroyVertArray(GLuint Buffer);
	void FillBuffers();
//	GLuint GetTextBool(){return }
	void Uniform();



	glm::mat4 getProjection() { return projection; };



	GLuint getFragmentShaderID() { return m_fragmentShaderID; };
	GLuint getVertexShaderID() { return m_vertexShaderID; };
	GLuint getShaderProgramID() { return m_shaderProgramID; };

protected:



private:




	//notes. camera pos 0,0,0. directon = 0,0,1. 

	glm::mat4 projection;

	glm::vec3 position;
	glm::vec3 camPosition;

	glm::mat4 viewMatrix;
	glm::mat4 modelMatrix;

	float movementX = 0;

	float movementY = 0;

	float time = 0;
//	GLuint m_
	GLuint m_fragmentShaderID;
	GLuint m_vertexShaderID;
	GLuint m_shaderProgramID;
	GLfloat VBODataStore[];
};


typedef Singleton<ShaderManager> TheShaderManager;
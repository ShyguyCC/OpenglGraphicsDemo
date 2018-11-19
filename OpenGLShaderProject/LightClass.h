#pragma once
#include "InputManager.h"
#include "MathsClass.h"
#include "ShaderManager.h"
#include <glew.h>


class LightClass
{
public:
	LightClass();
	~LightClass();

	void Draw();
	void Update();
	GLuint getVAO() { return VAO; };
	void UpdateMatrix();
	void ResetMatrix();

	void LoadIds();
	void deleteIds();
	void DrawTest();

private:

	GLuint lightPositionID;
	GLuint VAO = 0;
	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;

	GLuint vertexAttributeID;
	GLuint colorAttributeID;

	GLuint modelMatrixID;
	GLuint textureBool;
	GLuint islitBool;
	GLuint islitBoolFrag;

	GLuint lightColorID;


	glm::mat4 modelMatrix;
	glm::vec3 m_position;
	glm::vec3 lightingColor;

private:

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;


};


#pragma once

#include <iostream>
#include <glew.h>
#include <SDL.h>
#include <fstream>
#include <string>
#include "Singleton.h"
#include "InputManager.h"
#include "MathsClass.h"
#include "ShaderManager.h"
#include "TextureClass.h"

class BoxClass
{
public:
	BoxClass();
	~BoxClass();

	void SetSkyBoxIDs();
	void DrawSkyBox();
	void SetVecs(glm::vec3 FrontTopLeft, glm::vec3 FarBottemRight);
	void UpdateMatrix();
	void ResetMatrix();

	void CreateLightBoxIDs();
	void DrawLightBox();
	void DeleteLightBoxIDs();

private:

	GLuint normalUniformID;
	GLuint VAO = 0;
	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;
	GLuint EBO = 0;
	GLuint normalVBO = 0;
	GLfloat timer = 0;

	GLuint vertexAttributeID;
	GLuint colorAttributeID;

	GLuint textureVBO;
	GLuint textureAttributeID;
	GLuint TexturedID;
	GLuint modelMatrixID;
	GLuint textureBool;
	GLuint islitBool;
	GLuint islitBoolFrag;
	GLuint isWaterFallFrag;


	GLuint materialAmbientID;
	GLuint materialDiffuseID;
	GLuint materialSpecularID;
	GLuint materialShininessID;




	float m_shininess;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;


private:



	TextureClass TheTexture;
	TextureClass SkyBoxTexTest;

	glm::vec3 m_frontTopLeft;

	glm::vec3 m_farBottemRight;

	glm::mat4 projection;

	glm::vec3 camPosition;
	glm::vec3 camRotation;
	glm::mat4 viewMatrix;
	glm::mat4 modelMatrix;
	glm::mat3 normalMatrix;

	float RoationRad;


	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

};


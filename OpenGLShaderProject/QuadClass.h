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


class QuadClass
{
public:
	QuadClass();
	~QuadClass();

	void SetVecs(glm::vec3 topLeft, glm::vec3 bottemRight);
	void UpdateMatrix();
	void ResetMatrix();

	void CreateWallIds();
	void DrawWall();
	void DeleteWallIds();

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	void MoveQuad(glm::vec3 placement);

	void SetTexture(std::string filename);

	void MakeFloorIDs();

	void SetDimension(GLfloat width, GLfloat height);



	void SetPosition2D(glm::vec2 pos);
	void SetPosition3D(glm::vec3 pos);

	void FakeWaterFallEffect();
	void FakeWaterFallEffectDraw();

	void SimpleHUDIDs();
	void SimpleHUDDraw();
	void SimpleHUDTurtoralDraw();

	void GslCrossHatchIDs();
	void GslCrossHatchDraw();

	void SetEverythingCrossHatch(bool CrossHatcher) { CrossHatcherBool = CrossHatcher; };

private:

	bool CrossHatcherBool;
	GLfloat timer = 0;
	GLuint timerID;
	GLuint isWaterFallFrag;
	GLuint textureVBO = 0;
	GLuint VAO = 0;
	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;
	GLuint normalVBO = 0;
	GLuint EBO = 0;

	GLuint textureAttributeID;
	GLuint vertexAttributeID;
	GLuint colorAttributeID;
	GLuint normalAttributeID;

	GLuint modelMatrixID;
	GLuint textureBool;
	GLuint islitBool;
	GLuint islitBoolFrag;

	GLuint materialAmbientID;
	GLuint materialDiffuseID;
	GLuint materialSpecularID;
	GLuint materialShininessID;


	TextureClass TheTexture;
	TextureClass TheNewTexture;

	glm::vec3 m_topLeft; 
	glm::vec3 m_bottemRight;
	glm::vec3 camPosition;
	glm::vec3 m_dimension;

	glm::mat4 modelMatrix;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	float RoationRad;

private:

	float m_shininess;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};


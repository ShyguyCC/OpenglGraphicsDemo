#pragma once

#include <iostream>
#include <glew.h>
#include <SDL.h>
#include <fstream>
#include "ShaderManager.h"
#include "MathsClass.h"
#include "InputManager.h"

class CameraClass
{
public:
	CameraClass();
	~CameraClass();

	void SwitchTo3D();
	void SwitchTo2D();
	void projectionFunction(float hight, float width, bool PerspecOrOrtho);

	float getWidth() { return m_width; };
	float getHight() { return m_hight; };

	void Update();
	void NoMovementCam();
	

private:

	float m_hight;
	float m_width;

	float Pitch, Yaw;

	
	float RotationX, RotationY;

	glm::mat4 RotatorMat;
	
	glm::mat4 projection;

	glm::vec3 camPosition;


	glm::mat4 viewMatrix;
	glm::vec3 camRotation;
};

typedef Singleton<CameraClass> TheCamera;

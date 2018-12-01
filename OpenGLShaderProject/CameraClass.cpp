#include "CameraClass.h"



CameraClass::CameraClass(){
	camRotation = glm::vec3(0, 0, -1);
	RotationX = 0;
	RotationY = 0;
	Pitch = 0;
	Yaw = -90;
}


CameraClass::~CameraClass(){

}


void CameraClass::Update(){

	const Uint8* keys = TheInput::Instance()->GetKeyStates();
	int button = TheInput::Instance()->GetbuttonStatesFinal();
	int LeftStick = TheInput::Instance()->GetLeftStickState();
	int RightStick = TheInput::Instance()->GetRightStickState();
	glm::vec2 mouseVol = TheInput::Instance()->GetMouseVol();

	//Edit note, need to put this into better code, case switch statments.
	if (LeftStick == 1) {
		camPosition += camRotation * 0.1f;
	}
	else if (LeftStick == 2) {
		//we cross the view vector with the up vector and that gives us a vec pointing to the right.
		glm::vec3 strafeDirection = glm::cross(camRotation, glm::vec3(0, 1, 0));
		camPosition += strafeDirection * 0.1f;
	}
	else if (LeftStick == 3) {
		camPosition += camRotation * -0.1f;
	}
	else if (LeftStick == 4) {
		glm::vec3 strafeDirection = glm::cross(camRotation, glm::vec3(0, 1, 0));
		camPosition += strafeDirection * -0.1f;

	}
	else if (RightStick == 1) {
		Pitch += 0.3f;
	}
	else if (RightStick == 2) {
		Yaw += 0.3f;
	}
	else if (RightStick == 3) {
		Pitch -= 0.3f;
	}
	else if (RightStick == 4) {
		Yaw -= 0.3f;
	}else if (keys[SDL_SCANCODE_RIGHT])	{
		Yaw += 0.3f;
	}else if (keys[SDL_SCANCODE_LEFT]) {
		Yaw -= 0.3f;
	}else if (keys[SDL_SCANCODE_UP]) {
		Pitch += 0.3f;
	}
	else if (keys[SDL_SCANCODE_DOWN]) {
		Pitch -= 0.3f;
	}
	else if (keys[SDL_SCANCODE_W])
	{
		camPosition += camRotation * 0.1f;
	}
	else if (keys[SDL_SCANCODE_S]) {
		camPosition += camRotation * -0.1f;
	}else if (keys[SDL_SCANCODE_D])	{
		//cross cam rotation and up vec to get an vec showing where to strafe.
		glm::vec3 strafeDirection = glm::cross(camRotation, glm::vec3(0, 1, 0));
		camPosition += strafeDirection * 0.1f;
	}
	else if (keys[SDL_SCANCODE_A]) {
		glm::vec3 strafeDirection = glm::cross(camRotation, glm::vec3(0, 1, 0));
		camPosition += strafeDirection * -0.1f;
	}
	if (Pitch >= 80) {
		Pitch = 80;
	}
	else if (Pitch <= -80) {
		Pitch = -80;
	}
	if (Yaw >= 360) {
		Yaw = 0;
	}else if (Yaw <= -360) {
		Yaw = 0;
	}

	Yaw += mouseVol.x / 10;//yaw
	Pitch -= mouseVol.y / 10;//pitch


	camRotation.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	camRotation.y = sin(glm::radians(Pitch));
	camRotation.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));


	//here im not too sure so this is just testing out some stuff.
	GLuint viewMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "viewMatrix");
	GLuint projectionUniformID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "projection");
	//acquire vertex shader attribute IDs
	GLuint positionUniformID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "cameraPosition");
	//send camera position to vertex shader
	glUniform3fv(positionUniformID, 1, &camPosition.x);

	glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, &projection[0][0]);

	viewMatrix = glm::lookAt(camPosition, camPosition + camRotation, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
}

void CameraClass::NoMovementCam(){
	GLuint viewMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "viewMatrix");
	GLuint projectionUniformID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "projection");
	glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, &projection[0][0]);
	viewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
}


void CameraClass::projectionFunction(float hight, float width, bool PerspecOrOrtho) {

	m_hight = hight;
	m_width = width;
	if (PerspecOrOrtho) { // 3d
		projection = glm::perspective(glm::radians(60.0f), width / hight, 0.1f, 1000.0f);
	}
	else if (!PerspecOrOrtho) { //2d
		projection = glm::ortho(0.0f, width, 0.0f, hight);
	}
}

//these two functions made it a lot easyer to switch between the two modes, the function above is more of a setup so that we will have width and hight saved for this function.
void CameraClass::SwitchTo3D() {
	projection = glm::perspective(glm::radians(60.0f), m_width / m_hight, 0.1f, 1000.0f);
}

void CameraClass::SwitchTo2D() {
	projection = glm::ortho(0.0f, m_width, 0.0f, m_hight);
}

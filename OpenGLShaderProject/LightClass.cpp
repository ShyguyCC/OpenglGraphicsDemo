#include "LightClass.h"



LightClass::LightClass(){
	lightingColor.r = 1;
	lightingColor.g = 1;
	lightingColor.b = 1;
	m_ambient = glm::vec3(0.4f, 0.4f, 0.4f);
	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);



}


LightClass::~LightClass(){

}


void LightClass::Update(){

	const Uint8* keys = TheInput::Instance()->GetKeyStates();
	int button = TheInput::Instance()->GetbuttonStatesFinal();
	
	if (keys[SDL_SCANCODE_U]) {
		m_position.z -= 0.01f;
	} else if (keys[SDL_SCANCODE_J]) {
		m_position.x += 0.01f;
	}
	else if (keys[SDL_SCANCODE_H]) {
		m_position.x -= 0.01f;
	}
	else if (keys[SDL_SCANCODE_N]) {

		m_position.z += 0.01f;
	}
	else if (keys[SDL_SCANCODE_Y]) {

		m_position.y += 0.01f;
	}
	else if (keys[SDL_SCANCODE_I]) {

		m_position.y -= 0.01f;
	}
	if (button == SDL_CONTROLLER_BUTTON_Y) {
		m_position.z -= 0.01f;
	}
	else if (button == SDL_CONTROLLER_BUTTON_B) {
		m_position.x += 0.01f;
	}
	else if (button == SDL_CONTROLLER_BUTTON_X) {
		m_position.x -= 0.01f;
	}
	else if (button == SDL_CONTROLLER_BUTTON_A) {

		m_position.z += 0.01f;
	}
	else if (button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
		m_position.y += 0.01f;
	}
	else if (button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
		m_position.y -= 0.01f;
	}
	

}

void LightClass::UpdateMatrix() {

	ResetMatrix();
	modelMatrix = glm::translate(modelMatrix, m_position);

}

//modelMatrix = glm::rotate(modelMatrix, glm::radians(1.0f), glm::vec3(0, 0, 1));
void LightClass::ResetMatrix() {
	glm::mat4 temp;
	modelMatrix = temp;
}

void LightClass::DrawTest() {

	glUniform3fv(lightPositionID, 1, &m_position.x);
	glUniform1i(islitBool, 0);

	UpdateMatrix();
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glPointSize(25.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	ResetMatrix();
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

}

void LightClass::LoadIds() {
	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f };
	GLfloat colors[] = { 0.0f, 0.0f, 1.0f };

	vertexVBO = 0;
	colorVBO = 0;

	vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");

	modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix");
	lightColorID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "lightColor");
	islitBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");

	//------------------------------------------------------------------------------------------------------------------


	lightPositionID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "light.position");
	// we will only be using this on loadup.
	GLuint lightAmbientID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "light.ambient");
	GLuint lightDiffuseID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "light.diffuse");
	GLuint lightSpecularID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "light.specular");
	GLuint attConstantID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "light.attConstant");
	GLuint attLinearID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "light.attLinear");
	GLuint attQuadraticID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "light.attQuadratic");



	
	glUniform3fv(lightAmbientID, 1, &m_ambient.r);
	glUniform3fv(lightDiffuseID, 1, &m_diffuse.r);
	glUniform3fv(lightSpecularID, 1, &m_specular.r);

	glUniform1f(attConstantID, 0.2f);
	glUniform1f(attLinearID, 0.07f);
	glUniform1f(attQuadraticID, 0.017f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);


	glBindVertexArray(VAO);

	//fill and link vertex VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	//fill and link color VBO
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeID);
	glBindVertexArray(0);


	//this may be used in update for when we want changing colour lights.
	glUniform3f(lightColorID, lightingColor.r, lightingColor.g, lightingColor.b);


}

void LightClass::deleteIds() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
}
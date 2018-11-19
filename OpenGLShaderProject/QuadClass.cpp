#include "QuadClass.h"


//notes on scaling and the likes, make sure that the varables in the vector affacting the matrix aint static. they need to be open and then at the end of each draw just have a matrix = blah blah.

QuadClass::QuadClass(){
	RoationRad = 0;
	m_shininess = 32.0f;
	m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	m_diffuse = glm::vec3(0.5f, 0.0f, 0.0f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	CrossHatcherBool = true;
}


QuadClass::~QuadClass(){

}

void QuadClass::SetVecs(glm::vec3 topLeft, glm::vec3 bottemRight){
	m_topLeft = topLeft;
	m_bottemRight = bottemRight;
}

void QuadClass::UpdateMatrix(){
	ResetMatrix();
	modelMatrix = glm::translate(modelMatrix, m_position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(RoationRad), glm::vec3(0, 0, 1));
}

void QuadClass::ResetMatrix(){
	glm::mat4 temp;
	modelMatrix = temp;
}

void QuadClass::CreateWallIds(){
	GLfloat vertices[] = { m_topLeft.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_bottemRight.y, m_bottemRight.z,
		m_topLeft.x, m_bottemRight.y, m_bottemRight.z };

	//data that represents colors for quad image
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f };
	GLuint indices[] = { 0, 1, 3,
		3, 1, 2 };

	GLfloat normals[] = {
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	GLfloat UVs[] = { 0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f };

	VAO = 0;
	vertexVBO = 0;
	colorVBO = 0;
	EBO = 0;
	textureVBO = 0;
	normalVBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &normalVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);

	// vert attributes
	vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	normalAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "normalIn");
	GLuint textureAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "textureIn");

	// uniform
	modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix"); // new code.
	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	islitBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");

	//acquire vertex shader attribute IDs that we only need for this fuunction, as we are just loading material data that wont be changed.
	GLuint materialAmbientID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.ambient");
	GLuint materialDiffuseID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.diffuse");
	GLuint materialSpecularID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.specular");
	GLuint materialShininessID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.shininess");

	//send floor's material color to vertex shader
	glUniform3fv(materialAmbientID, 1, &m_ambient.r);
	glUniform3fv(materialDiffuseID, 1, &m_diffuse.r);
	glUniform3fv(materialSpecularID, 1, &m_specular.r);
	glUniform1f(materialShininessID, m_shininess);
	glUniform1i(textureBool, true);

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

	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normalAttributeID);

	//fill texture stuff
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
	glVertexAttribPointer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureAttributeID);

	//fill EBO with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void QuadClass::DrawWall(){
	glUniform3fv(materialAmbientID, 1, &m_ambient.r);
	glUniform3fv(materialDiffuseID, 1, &m_diffuse.r);
	glUniform3fv(materialSpecularID, 1, &m_specular.r);
	glUniform1f(materialShininessID, m_shininess);
	glUniform1i(textureBool, 1);
	glUniform1i(islitBool, 0);
	glUniform1i(islitBoolFrag, 1);
	glBindTexture(GL_TEXTURE_2D, TheNewTexture.getTextID());
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void QuadClass::DeleteWallIds(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &textureVBO);
	glDeleteBuffers(1, &normalVBO);
	glDeleteBuffers(1, &EBO);

}

void QuadClass::MakeFloorIDs() {
	GLfloat vertices[] = { m_topLeft.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_bottemRight.y, m_bottemRight.z,
		m_topLeft.x, m_bottemRight.y, m_bottemRight.z };

	//data that represents colors for quad image
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f };
	GLuint indices[] = { 0, 1, 3,
		3, 1, 2 };

	GLfloat normals[] = {
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	GLfloat UVs[] = { 0.0f, 0.0f,
		5.0f, 0.0f,
		5.0f, 5.0f,
		0.0f, 5.0f };


	VAO = 0;
	vertexVBO = 0;
	colorVBO = 0;
	EBO = 0;
	textureVBO = 0;
	normalVBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &normalVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);

	// vert attributes
	vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	normalAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "normalIn");
	GLuint textureAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "textureIn");

	// uniform
	modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix"); // new code.
	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	islitBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");

	//acquire vertex shader attribute IDs that we only need for this fuunction, as we are just loading material data that wont be changed.
	GLuint materialAmbientID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.ambient");
	GLuint materialDiffuseID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.diffuse");
	GLuint materialSpecularID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.specular");
	GLuint materialShininessID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.shininess");

	//send floor's material color to vertex shader
	glUniform3fv(materialAmbientID, 1, &m_ambient.r);
	glUniform3fv(materialDiffuseID, 1, &m_diffuse.r);
	glUniform3fv(materialSpecularID, 1, &m_specular.r);
	glUniform1f(materialShininessID, m_shininess);
	glUniform1i(textureBool, true);

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

	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normalAttributeID);

	//fill texture stuff
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
	glVertexAttribPointer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureAttributeID);

	//fill EBO with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void QuadClass::RotateX(float angle){
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1,0,0));
}

void QuadClass::RotateY(float angle){
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0, 1, 0));
}

void QuadClass::RotateZ(float angle){
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0, 0, 1));
}

void QuadClass::MoveQuad(glm::vec3 placement){
	modelMatrix = glm::translate(modelMatrix, placement);
}

void QuadClass::SetTexture(std::string filename){
	TheNewTexture.loadTexture(filename);
}

void QuadClass::SetDimension(GLfloat width, GLfloat height) {
	m_dimension = glm::vec3(width, height, 1.0f);
}

//for defult setting possition in 2d space
void QuadClass::SetPosition2D(glm::vec2 pos){
	m_position = glm::vec3(pos, 0.0f);
}

void QuadClass::SetPosition3D(glm::vec3 pos) {
	m_position = pos;
}

void QuadClass::FakeWaterFallEffect(){
	GLfloat vertices[] = { m_topLeft.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_bottemRight.y, m_bottemRight.z,
		m_topLeft.x, m_bottemRight.y, m_bottemRight.z };

	//data that represents colors for quad image
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f };
	GLuint indices[] = { 0, 1, 3,
		3, 1, 2 };

	GLfloat normals[] = {
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	GLfloat UVs[] = { 0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f };

	VAO = 0;
	vertexVBO = 0;
	colorVBO = 0;
	textureVBO = 0;
	EBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);

	// vert attributes
	GLuint vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	GLuint colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	GLuint textureAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "textureIn");

	// uniform
	GLuint modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix"); // new code.

	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	islitBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");
	isWaterFallFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "testFun");

	timerID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "time");

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

	//fill texture stuff
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
	glVertexAttribPointer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureAttributeID);

	//fill EBO with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void QuadClass::FakeWaterFallEffectDraw() {
	glUniform1i(textureBool, 0);
	glUniform1i(islitBool, 0);
	glUniform1i(islitBoolFrag, 0);
	glUniform1i(isWaterFallFrag, 1);
	glUniform1f(timerID, timer);
	//here is where we draw the thing.
	UpdateMatrix();
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// we call this flag a secound time because it says this bool into the shader, we will be only using this function for this function and nothing else, 
	// itll be easyer to call it once than to keep calling it every object.
	glUniform1i(isWaterFallFrag, 0);
	timer = SDL_GetTicks() / 100;
	timer = timer / 8;
	//we divide the time by because the shader speed of the water falling is waaay to fast otherwise.
}


void QuadClass::GslCrossHatchIDs() {

	GLfloat vertices[] = { m_topLeft.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_bottemRight.y, m_bottemRight.z,
		m_topLeft.x, m_bottemRight.y, m_bottemRight.z };

	//data that represents colors for quad image
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f };
	GLuint indices[] = { 0, 1, 3,
		3, 1, 2 };

	GLfloat normals[] = {
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	GLfloat UVs[] = { 0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f };

	VAO = 0;
	vertexVBO = 0;
	colorVBO = 0;
	textureVBO = 0;
	EBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);

	// vert attributes
	GLuint vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	GLuint colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	GLuint textureAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "textureIn");

	// uniform
	GLuint modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix"); // new code.

	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	islitBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");
	isWaterFallFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "testFunTwo");

	timerID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "time");

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

	//fill texture stuff
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
	glVertexAttribPointer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureAttributeID);

	//fill EBO with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void QuadClass::GslCrossHatchDraw() {
	glUniform1i(textureBool, 0);
	glUniform1i(islitBool, 0);
	glUniform1i(islitBoolFrag, 0);
	glUniform1i(isWaterFallFrag, 1);
	UpdateMatrix();
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glBindTexture(GL_TEXTURE_2D, TheNewTexture.getTextID());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (CrossHatcherBool) {
		glUniform1i(isWaterFallFrag, 0);
	}
}

// we are gonna try to do the 2d textured ui thing here again to see if i can do it.
void QuadClass::SimpleHUDIDs() {

	GLfloat vertices[] = { m_topLeft.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_topLeft.y, m_topLeft.z,
		m_bottemRight.x, m_bottemRight.y, m_topLeft.z,
		m_topLeft.x, m_bottemRight.y, m_topLeft.z };

	//data that represents colors for quad image
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f };
	GLuint indices[] = { 0, 1, 3,
		3, 1, 2 };
	// can change the UV to a higher number so that it repeats
	GLfloat UVs[] = { 0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f };


	VAO = 0;
	vertexVBO = 0;
	colorVBO = 0;
	textureVBO = 0;
	EBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);

	
	// vert attributes
	vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	textureAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "textureIn");

	// uniform
	modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix"); // new code.
	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");
	islitBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");

	glUniform1i(textureBool, true);
	glUniform1i(islitBoolFrag, false);

	//bind all VBOs and shader attributes together with VAO
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

	//fill texture stuff
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
	glVertexAttribPointer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureAttributeID);

	//fill EBO with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

// simple note for when i look back at this for essay, i was silly with the guint vao = 0; as that would delete the vao after the function, took me much longer than
// it should of to figure that one out.
void QuadClass::SimpleHUDDraw() {
	glUniform1i(textureBool, 1);
	glUniform1i(islitBool, 0);
	glUniform1i(islitBoolFrag, 0);
	glBindTexture(GL_TEXTURE_2D, TheNewTexture.getTextID());
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::scale(modelMatrix, m_dimension);
	m_position.x = 2.8f;
	m_position.y = 16.6f;
	modelMatrix = glm::translate(modelMatrix, m_position);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void QuadClass::SimpleHUDTurtoralDraw() {
	glUniform1i(textureBool, 1);
	glUniform1i(islitBool, 0);
	glUniform1i(islitBoolFrag, 0);
	glBindTexture(GL_TEXTURE_2D, TheNewTexture.getTextID());
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::scale(modelMatrix, m_dimension);
	modelMatrix = glm::translate(modelMatrix, m_position);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
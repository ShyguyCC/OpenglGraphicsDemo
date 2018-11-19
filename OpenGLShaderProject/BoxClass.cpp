#include "BoxClass.h"





BoxClass::BoxClass(){
	camRotation.z = -1;
	SkyBoxTexTest.loadTexture("Textures\\Mettle_Skybox_Cubic_Cross.jpg");
	RoationRad = 0;
	m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	m_shininess = 32.0f;
}


BoxClass::~BoxClass(){

}

void BoxClass::SetVecs(glm::vec3 FrontTopLeft, glm::vec3 FarBottemRight){
	m_frontTopLeft = FrontTopLeft;
	m_farBottemRight = FarBottemRight;
}

void BoxClass::DrawSkyBox(){
	glUniform1i(textureBool, 1);
	glUniform1i(islitBoolFrag, 0);
	glBindTexture(GL_TEXTURE_2D, SkyBoxTexTest.getTextID());

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void BoxClass::SetSkyBoxIDs() {
	GLfloat vertices[] = { m_frontTopLeft.x, m_frontTopLeft.y, m_frontTopLeft.z, m_farBottemRight.x, m_frontTopLeft.y, m_frontTopLeft.z,
		m_farBottemRight.x, m_farBottemRight.y, m_frontTopLeft.z, m_frontTopLeft.x, m_farBottemRight.y, m_frontTopLeft.z,

		m_frontTopLeft.x, m_frontTopLeft.y, m_farBottemRight.z, m_farBottemRight.x, m_frontTopLeft.y, m_farBottemRight.z,
		m_farBottemRight.x, m_farBottemRight.y, m_farBottemRight.z, m_frontTopLeft.x, m_farBottemRight.y, m_farBottemRight.z, //back face

		m_frontTopLeft.x,  m_frontTopLeft.y, m_farBottemRight.z, m_frontTopLeft.x, m_frontTopLeft.y, m_frontTopLeft.z,
		m_frontTopLeft.x, m_farBottemRight.y, m_frontTopLeft.z, m_frontTopLeft.x, m_farBottemRight.y, m_farBottemRight.z, //left face //---------------------------

		m_farBottemRight.x, m_frontTopLeft.y, m_farBottemRight.z, m_farBottemRight.x, m_frontTopLeft.y, m_frontTopLeft.z,
		m_farBottemRight.x, m_farBottemRight.y, m_frontTopLeft.z, m_farBottemRight.x, m_farBottemRight.y, m_farBottemRight.z, //right face

		m_frontTopLeft.x, m_frontTopLeft.y, m_farBottemRight.z, m_farBottemRight.x, m_frontTopLeft.y, m_farBottemRight.z,
		m_farBottemRight.x, m_frontTopLeft.y, m_frontTopLeft.z, m_frontTopLeft.x, m_frontTopLeft.y, m_frontTopLeft.z, //top face

		m_frontTopLeft.x, m_farBottemRight.y, m_farBottemRight.z, m_farBottemRight.x, m_farBottemRight.y, m_farBottemRight.z,
		m_farBottemRight.x, m_farBottemRight.y, m_frontTopLeft.z, m_frontTopLeft.x, m_farBottemRight.y, m_frontTopLeft.z }; //bottom face

																															// dont really need colors now. but it is here just in case.
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //red front face

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //green back face

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //blue left face

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //cyan right face
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //yellow top face
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }; //purple bottom face 


	GLuint indices[] = { 0, 1, 3, 3, 1, 2, //front face
		4, 5, 7, 7, 5, 6, //back face
		8, 9, 11, 11, 9, 10, //left face
		12, 13, 15, 15, 13, 14, //right face
		16, 17, 19, 19, 17, 18, //top face
		20, 21, 23, 23, 21, 22 }; //bottom face

	GLfloat UVs[] = {
		0.5f, 0.33333f,	0.25f, 0.33333f,  0.25f, 0.66f , 0.5f, 0.66f, //back

		0.75f, 0.33333f, 1.0f, 0.33333f, 1.0f, 0.66f, 0.75f, 0.66f , //front

		0.75f, 0.33333f, 0.5f, 0.33333f, 0.5f, 0.66f ,  0.75f, 0.66f, // left

		0.0f, 0.33333f, 0.25f, 0.33333f, 0.25f, 0.66f , 0.0f, 0.66f, // right

		0.5f, 0.0f, 0.25f, 0.0f, 0.25f, 0.33f,  0.5f, 0.33f,// top

		0.5f, 1.0f, 0.25f, 1.0f, 0.25f, 0.66f, 0.5f, 0.66f  // bottom
	};

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

	//ids only need to be done once, this could be done in a start up function.

	// vert attributes
	vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	textureAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "textureIn");

	// uniform
	modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix"); // new code.

	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");

	islitBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");

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

void BoxClass::UpdateMatrix() {
	ResetMatrix();
	modelMatrix = glm::translate(modelMatrix, m_position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(RoationRad), glm::vec3(0, 0, 1));
	normalMatrix = glm::inverse(glm::mat3(modelMatrix));
}

void BoxClass::ResetMatrix(){
	glm::mat4 temp;
	modelMatrix = temp;
}

//keeping this in here to show that i can get a box lit up, but wont be using this in the scene because i think that i show enough in there.
void BoxClass::CreateLightBoxIDs(){
	GLfloat vertices[] = { m_frontTopLeft.x, m_frontTopLeft.y, m_frontTopLeft.z, m_farBottemRight.x, m_frontTopLeft.y, m_frontTopLeft.z,
		m_farBottemRight.x, m_farBottemRight.y, m_frontTopLeft.z, m_frontTopLeft.x, m_farBottemRight.y, m_frontTopLeft.z,

		m_frontTopLeft.x, m_frontTopLeft.y, m_farBottemRight.z, m_farBottemRight.x, m_frontTopLeft.y, m_farBottemRight.z,
		m_farBottemRight.x, m_farBottemRight.y, m_farBottemRight.z, m_frontTopLeft.x, m_farBottemRight.y, m_farBottemRight.z, //back face
																															  //3 //blue left face
		m_frontTopLeft.x,  m_frontTopLeft.y, m_farBottemRight.z, m_frontTopLeft.x, m_frontTopLeft.y, m_frontTopLeft.z,
		m_frontTopLeft.x, m_farBottemRight.y, m_frontTopLeft.z, m_frontTopLeft.x, m_farBottemRight.y, m_farBottemRight.z, //left face //---------------------------
																														  //4 //cyan right face
		m_farBottemRight.x, m_frontTopLeft.y, m_farBottemRight.z, m_farBottemRight.x, m_frontTopLeft.y, m_frontTopLeft.z,
		m_farBottemRight.x, m_farBottemRight.y, m_frontTopLeft.z, m_farBottemRight.x, m_farBottemRight.y, m_farBottemRight.z, //right face
																															  //5 //yellow top face
		m_frontTopLeft.x, m_frontTopLeft.y, m_farBottemRight.z, m_farBottemRight.x, m_frontTopLeft.y, m_farBottemRight.z,
		m_farBottemRight.x, m_frontTopLeft.y, m_frontTopLeft.z, m_frontTopLeft.x, m_frontTopLeft.y, m_frontTopLeft.z, //top face
																													  //6 //purple bottom face 
		m_frontTopLeft.x, m_farBottemRight.y, m_farBottemRight.z, m_farBottemRight.x, m_farBottemRight.y, m_farBottemRight.z,
		m_farBottemRight.x, m_farBottemRight.y, m_frontTopLeft.z, m_frontTopLeft.x, m_farBottemRight.y, m_frontTopLeft.z }; //bottom face

	GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,//red front face

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //green back face

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //blue left face

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //cyan right face
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //yellow top face
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }; //purple bottom face 

	GLuint indices[] = { 0, 1, 3, 3, 1, 2, //front face
		4, 5, 7, 7, 5, 6, //back face
		8, 9, 11, 11, 9, 10, //left face
		12, 13, 15, 15, 13, 14, //right face
		16, 17, 19, 19, 17, 18, //top face
		20, 21, 23, 23, 21, 22 }; //bottom face

	GLfloat normals[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //front face

		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, //back face

		-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //left face

		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //right face

		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //top face

		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f };

	 VAO = 0;
	 vertexVBO = 0;
	 colorVBO = 0;
	 normalVBO = 0;
	 EBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &normalVBO);
	glGenBuffers(1, &EBO);

	// vert attributes
	GLuint vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	GLuint colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	GLuint normalAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "normalIn");

	// uniform
	GLuint modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix"); // new code.
	normalUniformID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "normalMatrix");
	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	islitBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");

	//acquire vertex shader attribute IDs that we only need for this fuunction, as we are just loading material data that wont be changed.
	materialAmbientID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.ambient");
	materialDiffuseID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.diffuse");
	materialSpecularID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.specular");
	materialShininessID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "material.shininess");

	glUniform3fv(materialAmbientID, 1, &m_ambient.r);
	glUniform3fv(materialDiffuseID, 1, &m_diffuse.r);
	glUniform3fv(materialSpecularID, 1, &m_specular.r);
	glUniform1f(materialShininessID, m_shininess);
	glUniform1i(textureBool, 0);
	glUniform1i(islitBool, 1);
	glUniform1i(islitBoolFrag, 1);
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

	//fill EBO with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}



void BoxClass::DrawLightBox(){

	glUniform3fv(materialAmbientID, 1, &m_ambient.r);
	glUniform3fv(materialDiffuseID, 1, &m_diffuse.r);
	glUniform3fv(materialSpecularID, 1, &m_specular.r);
	glUniform1f(materialShininessID, m_shininess);

	glUniform1i(textureBool, 0);
	glUniform1i(islitBool, 1);
	glUniform1i(islitBoolFrag, 1);

	UpdateMatrix();

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix3fv(normalUniformID, 1, GL_TRUE, &normalMatrix[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void BoxClass::DeleteLightBoxIDs() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &normalVBO);
	glDeleteBuffers(1, &EBO);
}

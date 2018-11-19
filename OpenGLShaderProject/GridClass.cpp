#include "GridClass.h"



GridClass::GridClass(){
	offset = 0;
	VAO = 0;
	vertexVBO = 0;
	colorVBO = 0;
}


GridClass::~GridClass(){

}

void GridClass::CreateGrid(){


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);

	GLuint vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	GLuint colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix");

	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");

	glBindVertexArray(VAO);

	//fill and link vertex VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	//fill and link color VBO
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeID);


	for (int i = 0; i < 21; i++){
		GLfloat vertices[] = { (GLfloat)(-10 + i), 0.0f, 10.0f, 
		(GLfloat)(-10 + i), 0.0f, -10.0f };
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colors), colors);

		offset += 24;
	}
//	(GLfloat)(-10 + i)
//	(GLfloat)(-10 + i)
	for (int i = 0; i < 21; i++){
		GLfloat vertices[] = { 10.0f, 0.0f, (GLfloat)(-10 + i),
		-10.0f, 0.0f, (GLfloat)(-10 + i) };
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colors), colors);

		offset += 24;
	}


}

void GridClass::CreateGrid(float GridSize){

	GridSizeSave = (GridSize * 2) + 1;
	GridSizeSaveDraw = GridSizeSave * 4;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);

	GLuint vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	GLuint colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix");

	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	lightBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");


	glBindVertexArray(VAO);

	//fill and link vertex VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	//fill and link color VBO
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeID);





	for (int i = 0; i < GridSizeSave; i++){

		GLfloat vertices[] = { (GLfloat)(-GridSize + i), 0.0f, GridSize,(GLfloat)(-GridSize + i), 0.0f, -GridSize };
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colors), colors);

		offset += 24;
	}

	for (int i = 0; i < GridSizeSave; i++) {
		GLfloat vertices[] = { GridSize, 0.0f, (GLfloat)(-GridSize + i),
			-GridSize, 0.0f, (GLfloat)(-GridSize + i) };
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colors), colors);

		offset += 24;
	}


}

void GridClass::DrawGrid(){
	glUniform1i(textureBool, 0);
	glUniform1i(lightBool, 0);
	glUniform1i(islitBoolFrag, false);
	


	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &BlankMatrix[0][0]);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 84);
	glBindVertexArray(0);
}

void GridClass::DrawCustomeGrid(){
	glUniform1i(textureBool, false);
	glUniform1i(lightBool, false);
	glUniform1i(islitBoolFrag, false);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &BlankMatrix[0][0]);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, GridSizeSaveDraw);
	glBindVertexArray(0);
}

#include "TextClass.h"



TextClass::TextClass(){
	//16x16
	TheTexture.loadTexture("Text\\Calibri.png");
	cellDimension = glm::vec2(1.0f / 16.0f, 1.0f / 16.0f);
}


TextClass::~TextClass(){

}

void TextClass::LoadText(){

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &colorVBO);

	GLuint vertexAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "vertexIn");
	GLuint colorAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "colorIn");
	GLuint textureAttributeID = glGetAttribLocation(TheShaderManager::Instance()->getShaderProgramID(), "textureIn");


	modelMatrixID = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "modelMatrix");

	textureBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isTexturedout");
	islitBoolFrag = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLitfrag");
	lightBool = glGetUniformLocation(TheShaderManager::Instance()->getShaderProgramID(), "isLit");

	glUniform1i(textureBool, true);

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

	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureAttributeID);




	int blah = 0;
	std::string str = "HELLO";
	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {

		GLfloat vertices[] = { (GLfloat)(-500 + blah), 500.0f, 0.0f,
			(GLfloat)(-500 + blah), 500.0f, 0.0f };
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colors), colors);



		textureIndex = str[blah];
		//here is where we will do the coding blah blah.

		textureCell.s = textureIndex % 16;
		textureCell.t = textureIndex / 16;
		//std::cout << "text co ord t  = " << textureCell.t << ". text co ord s = " << textureCell.s << std::endl;

		//the table for x was showing the right value but on the wrong side.
		textureCell.s = 16 - textureCell.s;

		glm::vec2 texCoordOrigin = textureCell * cellDimension;
		//std::cout << str[blah] << " = " << textureIndex << std::endl;
		//std::cout << "text co ord x = " << texCoordOrigin.x << ". text co ord y = " << texCoordOrigin.y << std::endl;

		GLfloat UVs[] = { texCoordOrigin.x, texCoordOrigin.y,
			(texCoordOrigin.x + cellDimension.x), texCoordOrigin.y,
			(texCoordOrigin.x + cellDimension.x), (texCoordOrigin.y + cellDimension.y),
			texCoordOrigin.x, (texCoordOrigin.y + cellDimension.y) };

		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offsetText, sizeof(UVs), UVs);


		offset += 24;
		offsetText += 32;


		blah++;
	}

	DrawingFloat = blah * 4;


}
//sorry i just cant get text to work.

void TextClass::DrawText(){



	glUniform1i(textureBool, 0);
	glUniform1i(lightBool, 0);
	glUniform1i(islitBoolFrag, false);


//	glBindTexture(GL_TEXTURE_2D, TheTexture.getTextID());

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &BlankMatrix[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, DrawingFloat, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
//	glBindTexture(GL_TEXTURE_2D, 0);
}



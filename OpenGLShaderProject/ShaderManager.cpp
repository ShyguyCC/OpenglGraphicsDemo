#include "ShaderManager.h"



ShaderManager::ShaderManager(){

}


ShaderManager::~ShaderManager(){

}

bool ShaderManager::CreateProgram(){

	m_shaderProgramID = glCreateProgram();
	if (m_shaderProgramID == 0)
	{
		//shader program could not be created
	}



	return false;
}

bool ShaderManager::CreateShaders(){
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0)
	{
		//vertex shader could not be created
		std::cout << "vertex shader could not be created" << std::endl;
		return false;
	}
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0)
	{
		//fragment shader could not be created
		std::cout << "fragment shader could not be created" << std::endl;
		return false;
	}


	return true;
}

// more marks to have this function input a way to do both frag and vert depending on the inputted file.
bool ShaderManager::CompileShaders(){

	//from here
	std::fstream file;
	std::string lineText = "";
	std::string finalString = "";
	file.open("ShaderFile\\Main.vert");
	if (!file)
	{
		//error opening vertex shader file
	}
	
	while (!file.eof())
	{
		getline(file, lineText);
		finalString += lineText + "\n";
	}
	file.close();


	const GLchar* finalCode = (const GLchar*)(finalString.c_str());

	glShaderSource(m_vertexShaderID, 1, &finalCode, NULL);

	glCompileShader(m_vertexShaderID);
	//to here is vertex shader only, will need to make a fragment one.

	/*
	//compile fragment shader code
	glShaderSource(m_fragmentShaderID, 1, &finalCode, NULL);
	
	glCompileShader(m_fragmentShaderID);
	*/
	// this gets any error that may happen.
	GLint errorCode;
	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &errorCode);

	if (errorCode == GL_TRUE) {

		std::cout << "theres been no error" << std::endl;
	}
	else { // if theres been no errors
		std::cout << "theres been an error m_vertexShaderID" << std::endl;
		GLchar errorMessage[1000];
		GLsizei length = 1000;

		glGetShaderInfoLog(m_vertexShaderID, 1000, &length, errorMessage);
		std::cout << errorMessage << std::endl;

		return false;
	}


	
//	std::fstream file;
	lineText = "";
	finalString = "";
	file.open("ShaderFile\\Main.frag");
	if (!file)
	{
		//error opening vertex shader file
	}

	while (!file.eof())
	{
		getline(file, lineText);
		finalString += lineText + "\n";
	}
	file.close();


	finalCode = (const GLchar*)(finalString.c_str());


	//compile fragment shader code
	glShaderSource(m_fragmentShaderID, 1, &finalCode, NULL);

	glCompileShader(m_fragmentShaderID);

	glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &errorCode);

	if (errorCode == GL_TRUE) {

		std::cout << "theres been no error" << std::endl;
	}
	else { // if theres been no errors
		std::cout << "theres been an m_fragmentShaderID error" << std::endl;
		GLchar errorMessage[1000];
		GLsizei length = 1000;

		glGetShaderInfoLog(m_fragmentShaderID, 1000, &length, errorMessage);
		std::cout << errorMessage << std::endl;

		return false;
	}

	return true;
}



void ShaderManager::AttachShaders(){
	//vertex only
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	//fragment only
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);


}

bool ShaderManager::LinkProgram(){
	glLinkProgram(m_shaderProgramID);
	glUseProgram(m_shaderProgramID);
	GLint linkResult;
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_TRUE)
	{
		std::cout << "shader program did link!" << std::endl;
	}
	else {
		std::cout << "shader program did not link!" << std::endl;
		GLchar error[1000];
		GLsizei length = 1000;
		glGetProgramInfoLog(m_shaderProgramID, 1000, &length, error);
		std::cout << error << std::endl;
		return false;
	}
	return true;
}

void ShaderManager::DetachShaders(){
	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void ShaderManager::DestroyShaders(){
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}
//kills shader program
void ShaderManager::DestroyProgram(){
	glDeleteProgram(m_shaderProgramID);
}

void ShaderManager::CreateVertArray(GLuint Buffer) {
	glGenVertexArrays(1, &Buffer);
}

void ShaderManager::DestroyVertArray(GLuint Buffer) {
	glDeleteVertexArrays(1, &Buffer);
}

void ShaderManager::CreateBuffer(GLuint Buffer) {
	glGenBuffers(1, &Buffer);
}

void ShaderManager::DestroyBuffer(GLuint Buffer) {
	glDeleteBuffers(1, &Buffer);
}
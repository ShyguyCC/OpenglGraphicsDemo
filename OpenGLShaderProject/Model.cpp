#include <fstream>
#include <iostream>
#include <vector>
#include <gtc\matrix_transform.hpp>     
#include <gtc\type_ptr.hpp> 
#include "Model.h"
#include "ShaderManager.h"
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag reference
//------------------------------------------------------------------------------------------------------
bool& Model::IsTextured()
{

	return m_isTextured;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets shininess value of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetShininess(GLfloat shininess)
{

	m_shininess = shininess;

}
//------------------------------------------------------------------------------------------------------
//function that sets texture to model based on texture ID passed
//------------------------------------------------------------------------------------------------------
void Model::SetTexture(std::string textureID)
{

	m_texture.loadTexture(textureID);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets ambient component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{

	m_ambient = glm::vec3(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets diffuse component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{

	m_diffuse = glm::vec3(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets specular component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{

	m_specular = glm::vec3(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets position of model
//------------------------------------------------------------------------------------------------------
void Model::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{

	m_position = glm::vec3(x, y, z);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets rotation of model
//------------------------------------------------------------------------------------------------------
void Model::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{

	m_rotation = glm::vec3(x, y, z);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets scale of model
//------------------------------------------------------------------------------------------------------
void Model::SetScale(GLfloat x, GLfloat y, GLfloat z)
{

	m_scale = glm::vec3(x, y, z);

}
//------------------------------------------------------------------------------------------------------
//function that loads raw model data from OBJ file 
//------------------------------------------------------------------------------------------------------
bool Model::LoadModel(const std::string& filename)
{

	//variables to load and store all model data
	std::fstream file;
	std::string lineText = "";
	unsigned int tokenPosition = 0;

	std::vector<glm::vec3> faceArray;
	std::vector<glm::vec3> vertexArray;
	std::vector<glm::vec2> textureArray;
	std::vector<glm::vec3> normalArray;

	std::vector<std::string> subNumbers;
	std::vector<std::string> subStrings;

	//display text to state that file is being opened and read
	std::cout << "Opening and reading model file : " << "\"" << filename << "\"" << std::endl;

	//open model file
	file.open(filename);

	//if opening of model file failed, display error message
	if (!file)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//read in all model data until end of file is reached
	while (!file.eof())
	{

		//read line of text
		getline(file, lineText);

		//break text string into smaller substrings
		do
		{
			tokenPosition = lineText.find(' ');
			subStrings.push_back(lineText.substr(0, tokenPosition));
			lineText.erase(0, tokenPosition + 1);
		} while (tokenPosition != std::string::npos);

		//if first token is "v" or "vn", set the vertices and normal values
		if (subStrings[0] == "v" || subStrings[0] == "vn")
		{

			//if it's a vertex position, add it to the vertex array
			if (subStrings[0] == "v")
			{
				vertexArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
					(GLfloat)(atof(subStrings[2].c_str())),
					(GLfloat)(atof(subStrings[3].c_str()))));
			}

			//if it's a normal direction, add it to the normal array
			if (subStrings[0] == "vn")
			{
				normalArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
					(GLfloat)(atof(subStrings[2].c_str())),
					(GLfloat)(atof(subStrings[3].c_str()))));
			}

		}

		//if first token is "vt", set the UV data
		if (subStrings[0] == "vt")
		{

			//add to the textureArray
			textureArray.push_back(glm::vec2((GLfloat)(atof(subStrings[1].c_str())),
				(GLfloat)(atof(subStrings[2].c_str()))));

		}

		//if first token is "f", create a new face and set the face data
		if (subStrings[0] == "f")
		{

			//loop through all three face sub strings 
			for (int i = 1; i <= 3; i++)
			{

				//break each face substring into three face numeric values
				do
				{
					tokenPosition = subStrings[i].find('/');
					subNumbers.push_back(subStrings[i].substr(0, tokenPosition));
					subStrings[i].erase(0, tokenPosition + 1);
				} while (tokenPosition != std::string::npos);

				//add to face array
				faceArray.push_back(glm::vec3(atoi(subNumbers[0].c_str()) - 1,
					atoi(subNumbers[1].c_str()) - 1,
					atoi(subNumbers[2].c_str()) - 1));

				//clear numbers for next use
				subNumbers.clear();

			}

		}

		//clear the sub strings for next use
		subStrings.clear();

	}

	//close model file
	file.close();

	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//---------------------------------
	//sift through all data for EBO
	//---------------------------------

	std::vector<GLuint> indices;
	std::vector<Groups> groups;

	//loop through all triangle faces and individually build vertex groups out of them
	//then add each vertex group to the array but first check if it's already there and
	//if it is then skip it but mark EBO to point to that existing index
	//this alleviates the problem of creating a EBO out of OBJ model file data
	for (size_t i = 0; i < faceArray.size(); i++)
	{

		//create a temporary group
		Groups tri;
		tri.vertex = vertexArray[faceArray[i].x];
		tri.texture = textureArray[faceArray[i].y];
		tri.normal = normalArray[faceArray[i].z];

		//flag for element found
		bool isFound = false;

		//set below for-loop starting point to always go 5 elements back
		//so that we don't loop through entire group array each time
		int loopStart = (groups.size() >= 5 ? groups.size() - 5 : 0);

		//loop through existing groups to see if this group already exists in there
		//and if its found use that index for the EBO otherwise continue searching
		for (size_t j = loopStart; j < groups.size(); j++)
		{

			if (tri.vertex == groups[j].vertex &&
				tri.texture == groups[j].texture &&
				tri.normal == groups[j].normal)
			{
				indices.push_back(j);
				isFound = true;
				break;
			}

		}

		//if nothing was found, it's a new group so add it and index the EBO
		if (!isFound)
		{
			groups.push_back(tri);
			indices.push_back(groups.size() - 1);
		}

	}

	//stats for vertices saved
	std::cout << "Total Vertices : " << indices.size() << std::endl;
	std::cout << "Actual Vertices : " << groups.size() << std::endl;
	std::cout << "Vertex Space Saved : "
		<< 100 - (int)((float)(groups.size()) / (float)(indices.size()) * 100) << "%" << std::endl;

	//---------------------------------
	//add all data to VBOs
	//---------------------------------

	//storage for our vertex, texture and normal data
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> textures;
	std::vector<GLfloat> normals;

	//add all vertex, texture and normal data to the main vectors
	//from here this data will be fed into to VBO later on
	for (size_t j = 0; j < groups.size(); j++)
	{

		vertices.push_back(groups[j].vertex.x);
		vertices.push_back(groups[j].vertex.y);
		vertices.push_back(groups[j].vertex.z);

		textures.push_back(groups[j].texture.s);
		textures.push_back(groups[j].texture.t);

		normals.push_back(groups[j].normal.x);
		normals.push_back(groups[j].normal.y);
		normals.push_back(groups[j].normal.z);

	}

	//total up vertices for use in Draw() function
	m_totalVertices = indices.size();

	//bind all VBOs and shader attributes together with VAO
	glBindVertexArray(m_VAO);

	//fill and link vertex VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_vertexAttributeID);

	//fill and link texture VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
	glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(GLfloat), &textures[0], GL_STATIC_DRAW);
	glVertexAttribPointer(m_textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_textureAttributeID);

	//fill and link normal VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(m_normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_normalAttributeID);

	//fill EBO with indices 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}
//------------------------------------------------------------------------------------------------------
//function that loads in texture file for cube
//------------------------------------------------------------------------------------------------------
bool Model::LoadTexture(const std::string& filename, const std::string textureID)
{

//	return m_texture.Load(filename, textureID);
	return true;
}
//------------------------------------------------------------------------------------------------------
//function that unloads texture file for cube
//------------------------------------------------------------------------------------------------------
void Model::UnloadTexture(const std::string textureID)
{

//	m_texture.Unload(textureID);

}
//------------------------------------------------------------------------------------------------------
//function that creates and fills all buffers with vertex and color data 
//------------------------------------------------------------------------------------------------------
void Model::Create()
{

	//make sure model always exists
	m_scale = glm::vec3(1.0f);

	//set material color to ???
	m_shininess = 1.0f;
	m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specular = glm::vec3(1.0, 1.0f, 1.0f);
	
	//get shader program ID so that we can use it multiple times below
	GLuint shaderProgram = TheShaderManager::Instance()->getShaderProgramID();

	//may need to change the shader code around here and any other shader code that may be here.

	//get all uniform shader IDs from fragment shader relating to the MATERIAL
	m_materialAmbientID = glGetUniformLocation(shaderProgram, "Material.ambient");
	m_materialDiffuseID = glGetUniformLocation(shaderProgram, "Material.diffuse");
	m_materialSpecularID = glGetUniformLocation(shaderProgram, "Material.specular");
	m_materialShininessID = glGetUniformLocation(shaderProgram, "Material.shininess");

	//get all other shader IDs relating to texture flag, model matrix and attributes
	m_lightFlagID = glGetUniformLocation(shaderProgram, "isLitfrag");
	m_textureFlagID = glGetUniformLocation(shaderProgram, "isTexturedout");
	m_modelUniformID = glGetUniformLocation(shaderProgram, "modelMatrix");
	m_normalUniformID = glGetUniformLocation(shaderProgram, "normalMatrix");
	m_vertexAttributeID = glGetAttribLocation(shaderProgram, "vertexIn");
	m_colorAttributeID = glGetAttribLocation(shaderProgram, "colorIn");
	m_normalAttributeID = glGetAttribLocation(shaderProgram, "normalIn");
	m_textureAttributeID = glGetAttribLocation(shaderProgram, "textureIn");

	//create VAO, VBOs and EBO
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexVBO);
	glGenBuffers(1, &m_colorVBO);
	glGenBuffers(1, &m_normalVBO);
	glGenBuffers(1, &m_textureVBO);
	glGenBuffers(1, &m_EBO);

}
//------------------------------------------------------------------------------------------------------
//function that adjusts model's transformations
//------------------------------------------------------------------------------------------------------
void Model::Update()
{

	//set model and normal matrices to identity
	m_normal = glm::mat3(1.0f);
	m_model = glm::mat4(1.0f);

	//apply all transformations to model matrix
	m_model = glm::translate(m_model, m_position);

	m_model = glm::rotate(m_model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0));
	m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0));
	m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0));

	m_model = glm::scale(m_model, m_scale);

	//convert model matrix to 3x3 and invert it for normals to use in shader
	m_normal = glm::inverse(glm::mat3(m_model));

}
//------------------------------------------------------------------------------------------------------
//function that renders model on screen
//------------------------------------------------------------------------------------------------------
void Model::Draw()
{

	//send model matrix to vertex shader
	glUniformMatrix4fv(m_modelUniformID, 1, GL_FALSE, &m_model[0][0]);

	//send normal matrix to vertex shader
	glUniformMatrix3fv(m_normalUniformID, 1, GL_TRUE, &m_normal[0][0]);

	//send model's material color to fragment shader
	glUniform3fv(m_materialAmbientID, 1, &m_ambient.r);
	glUniform3fv(m_materialDiffuseID, 1, &m_diffuse.r);
	glUniform3fv(m_materialSpecularID, 1, &m_specular.r);
	glUniform1f(m_materialShininessID, m_shininess);

	//send lighting flag to fragment shader (ON)
	glUniform1i(m_lightFlagID, true);

	//only if model is set to be textured, pass texture ID to shader
	if (m_isTextured)
	{
		glUniform1i(m_textureFlagID, true);
		glBindTexture(GL_TEXTURE_2D, m_texture.getTextID());
	}

	else
	{
		glUniform1i(m_textureFlagID, false);
	}

	//bind VAO and render everything!
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_totalVertices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

}
//------------------------------------------------------------------------------------------------------
//function that destroys all buffer objects
//------------------------------------------------------------------------------------------------------
void Model::Destroy()
{

	//destroy EBO, VBOs and VAO
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_textureVBO);
	glDeleteBuffers(1, &m_normalVBO);
	glDeleteBuffers(1, &m_colorVBO);
	glDeleteBuffers(1, &m_vertexVBO);
	glDeleteVertexArrays(1, &m_VAO);

}
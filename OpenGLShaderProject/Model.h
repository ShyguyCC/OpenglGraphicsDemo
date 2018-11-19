#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <glew.h>
#include <glm.hpp>
#include "TextureClass.h"

//struct to store all three components of a vertex group, which is
//the grouping of verts, UVs and norms for each point in a triangle
struct Groups
{
	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
};

class Model
{

public:

	bool& IsTextured();

public:

	void SetShininess(GLfloat shininess);
	void SetTexture(std::string textureID);

	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetRotation(GLfloat x, GLfloat y, GLfloat z);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);

public:

	bool LoadModel(const std::string& filename);
	bool LoadTexture(const std::string& filename, const std::string textureID);
	void UnloadTexture(const std::string textureID);

public:

	void Create();
	void Update();
	void Draw();
	void Destroy();

private:

	bool m_isTextured;
	GLfloat m_shininess;

	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_vertexVBO;
	GLuint m_colorVBO;
	GLuint m_normalVBO;
	GLuint m_textureVBO;
	GLuint m_totalVertices;

	GLuint m_materialAmbientID;
	GLuint m_materialDiffuseID;
	GLuint m_materialSpecularID;
	GLuint m_materialShininessID;

	GLuint m_lightFlagID;
	GLuint m_textureFlagID;
	GLuint m_modelUniformID;
	GLuint m_normalUniformID;

	GLuint m_vertexAttributeID;
	GLuint m_colorAttributeID;
	GLuint m_normalAttributeID;
	GLuint m_textureAttributeID;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	glm::mat3 m_normal;
	glm::mat4 m_model;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	TextureClass m_texture;

};

#endif
#include "MathsClass.h"



MathsClass::MathsClass()
{
}


MathsClass::~MathsClass(){
}

//this adds a rotation to the matrix using the vector to determin which x y z to rotate.
glm::mat4 MathsClass::DotProduct(glm::mat4 Matrix, float Rotation, glm::vec3 Vector){
	Matrix = glm::rotate(Matrix, Rotation, Vector);
	return Matrix;
}


//convert vector to a homogenous coordinate before applying rotation
//convert vector back to a regular 3D vector (it’s now pointing up)
glm::vec3 MathsClass::homogenous(glm::mat4 Matrix, glm::vec3 Vector, float Magnatude){
	glm::vec4 homogenous = Matrix * glm::vec4(Vector, Magnatude);
	Vector = glm::vec3(homogenous);
	return Vector;
}




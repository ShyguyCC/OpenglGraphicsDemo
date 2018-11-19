#pragma once

#include <math.h>
#include <glm.hpp>
#include <gtx\vector_angle.hpp>
#include <gtx\euler_angles.hpp>
#include <gtx\projection.hpp>
#include "Singleton.h"
//this is a way to include any maths related stuff for other classes but may not be used in them.


class MathsClass
{
public:
	MathsClass();
	~MathsClass();

public:




	float VecAngle2V(glm::vec2 x, glm::vec2 y) {	float Temp = 0; Temp = glm::angle(x, y); return glm::degrees(Temp);	};
	float VecAngle3V(glm::vec3 x, glm::vec3 y) { float Temp = 0; Temp = glm::angle(x, y); return glm::degrees(Temp); };
	float VecAngle4V(glm::vec4 x, glm::vec4 y) { float Temp = 0; Temp = glm::angle(x, y); return glm::degrees(Temp); };

	glm::mat4 DotProduct(glm::mat4 Matrix, float Rotation, glm::vec3 Vector);

	glm::vec3 homogenous(glm::mat4 Matrix, glm::vec3 Vector, float Magnatude);

protected:

private:

};


typedef Singleton<MathsClass> TheMaths;

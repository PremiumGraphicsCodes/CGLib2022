#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Vector4d.h"

namespace Crystal {
	namespace Graphics {

class SpotLight {
public:
	SpotLight() :
		position(0, 0, 0),
		direction(1, 0, 0),
		diffuse(0, 0, 0, 0),
		ambient(0, 0, 0, 0),
		specular(0, 0, 0, 0)
	{
	}

	~SpotLight() {};

public:

	glm::vec3 getPosition() const { return position; }

	void setPosition(const glm::vec3& pos) { this->position = pos; }

	glm::vec3 getDirection() const { return direction; }

	void setDirection(const glm::vec3& dir) { this->direction = dir; }

	glm::vec4 getDiffuse() const { return diffuse; }

	void setDiffuse(const glm::vec4& d) { this->diffuse = d; }

	glm::vec4 getSpecular() const { return specular; }

	void setSpecular(const glm::vec4& s) { this->specular = s; }

	glm::vec4 getAmbient() const { return ambient; }

	void setAmbient(const glm::vec4& a) { this->ambient = a; }

private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec4 diffuse;
	glm::vec4 ambient;
	glm::vec4 specular;
};

	}
}
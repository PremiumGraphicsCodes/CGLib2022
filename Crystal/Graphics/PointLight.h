#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Vector4d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Graphics {

class PointLight {
public:
	PointLight() :
		position(0,0,0),
		diffuse(0,0,0,0),
		ambient(0,0,0,0),
		specular(0,0,0,0)
	{
	}

	~PointLight() {};

public:

	glm::vec4 getDiffuse() const { return diffuse; }

	void setDiffuse(const glm::vec4& d) { this->diffuse = d; }

	glm::vec4 getSpecular() const { return specular; }

	void setSpecular(const glm::vec4& s) { this->specular = s; }

	glm::vec4 getAmbient() const { return ambient; }

	void setAmbient(const glm::vec4& a) { this->ambient = a; }

	glm::vec3 getPosition() const { return position; }

	void setPosition(const glm::vec3& pos) { this->position = pos; }

	void move(const Math::Vector3dd& v) { this->position += v; }

	void transform(const Math::Matrix3dd& m) { position = m * position; }

	void transform(const Math::Matrix4dd& m) { position = m * glm::vec4(position,1.0); }

	PointLight* clone() const {
		PointLight* light = new PointLight();
		light->position = this->position;
		light->diffuse = this->diffuse;
		light->ambient = this->ambient;
		light->specular = this->specular;
		return light;
	}

private:
	glm::vec3 position;
	glm::vec4 diffuse;
	glm::vec4 ambient;
	glm::vec4 specular;
};

	}
}
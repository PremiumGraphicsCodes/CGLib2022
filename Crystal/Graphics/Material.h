#pragma once

#include <string>

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

struct Material
{
public:
	Material() :
		shininess(1.0f),
		ambient(0.0f, 0.0f, 0.0f, 0.0f),
		diffuse(0.0f, 0.0f, 0.0f, 0.0f),
		specular(0.0f, 0.0f, 0.0f, 0.0f),
		ambientTexName(""),
		diffuseTexName(""),
		specularTexName("")
	{}

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;

	std::string ambientTexName;
	std::string diffuseTexName;
	std::string specularTexName;
};

	}
}
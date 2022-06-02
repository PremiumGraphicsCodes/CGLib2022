#pragma once

#include "../Graphics/Imagef.h"

#include <string>

namespace Crystal {
	namespace IO {

struct MTL
{
	enum class Illumination
	{
		COLOR_ON_AND_AMBIENT_OFF = 0,
		COLOR_ON_AND_AMBIENT_ON = 1,
		HIGHLIGHT_ON = 2,
		REFRECTION_ON_AND_RAY_TRACE_ON = 3,

		REFLECTION_ON_AND_RAY_TRACE_OFF = 8,

		CAST_SHADOWS_ONTO_INVISIBLE_SURFACES = 10,
	};

	MTL() {
		ambient = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
		specular = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
		specularExponent = 1.0f;
		transparent = 0.0f;
		opticalDensity = 0.0f;

		illumination = Illumination::COLOR_ON_AND_AMBIENT_OFF;
	}

	/*
	void setOpticalDensity(const float d) {
		assert((0.001f <= d) && (d <= 10.0f));
		this->opticalDensity = d;
	}

	float getOpticalDensity() const { return opticalDensity; }
	*/

	//Graphics::Material toMaterial(const std::string& directory) const;

public:
	std::string name;
	Graphics::ColorRGBAf ambient;
	Graphics::ColorRGBAf diffuse;
	Graphics::ColorRGBAf specular;

	float specularExponent;
	float transparent;
	float opticalDensity;

	std::string ambientTexture;
	std::string diffuseTexture;
	std::string shininessTexture;
	std::string bumpTexture;

	Illumination illumination;
};

struct MTLFile
{
	std::vector<MTL> materials;

	MTL find(const std::string& name) {
		auto iter = std::find_if(materials.begin(), materials.end(), [=](const auto& m) { return m.name == name; });
		return *iter;
	}
};

	}
}
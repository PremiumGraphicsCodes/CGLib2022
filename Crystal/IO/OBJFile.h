#pragma once

#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"
#include <string>
#include <vector>

namespace Crystal {
	namespace IO {

struct OBJFace
{
	std::vector<unsigned int> positionIndices;
	std::vector<int> normalIndices;
	std::vector<int> texCoordIndices;
};

struct OBJGroup
{
	std::string name;
	std::string usemtl;
	std::vector< OBJFace > faces;
};

struct OBJFile
{
	std::string comment;

	std::vector< Math::Vector3df > positions;
	std::vector< Math::Vector3df > normals;
	std::vector< Math::Vector2df > texCoords;

	std::vector< OBJGroup > groups;
	std::vector< std::string > mtllibs;
};

	}
}
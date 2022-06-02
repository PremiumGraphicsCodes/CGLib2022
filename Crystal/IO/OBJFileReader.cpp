#include "OBJFileReader.h"

#include <fstream>
#include <cassert>
#include <vector>

#include "../Math/Vector3d.h"
#include "../Shape/Vertex.h"
#include "../Shape/Face.h"
//#include "../Scene/PolygonMesh.h"

#include "OBJSyntaxParser.h"

#include "Helper.h"

#include <string>
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shape;
using namespace Crystal::IO;

bool OBJFileReader::read(const std::filesystem::path& filePath)
{
	std::ifstream stream;
	stream.open(filePath);

	if (!stream.is_open()) {
		return false;
	}

	return read(stream);
}

bool OBJFileReader::read(std::istream& stream)
{
	std::string header;
	std::string currentMtllibName;

	auto currentGroup = OBJGroup();

	while (!stream.eof()) {
		std::string line;
		std::getline(stream, line);
		const auto strs = Helper::split(line, ' ');
		if(strs.empty()) {
			continue;
		}
		const auto header = strs.front();
		if (header == "#") {
		}
		else if (header == "v") {
			obj.positions.push_back(readVertices(strs));
		}
		else if (header == "vt") {
			obj.texCoords.push_back(readVector2d(strs));
		}
		else if (header == "vn" || header == "-vn") {
			obj.normals.push_back(readVector3d(strs));
		}
		else if (header == "mtllib") {
			currentMtllibName = strs[1];
			obj.mtllibs.push_back(currentMtllibName);
		}
		else if (header == "usemtl") {
			currentGroup.usemtl = strs[1];
			//mtllibMap.insert(std::make_pair(currentMtllibName, currentUseMtlName));
		}
		else if (header == "f") {
			//std::vector< std::string >& strs = Helper::split(str, ' ');

			OBJFace face = OBJSyntaxParser::parseFaceLine(line);

			currentGroup.faces.push_back(face);
		}
		else if (header == "g") {
			if (strs.size() >= 2) {
				currentGroup.name = strs[1];
			}
			if (!currentGroup.faces.empty()) {
				obj.groups.push_back(currentGroup);
				currentGroup = OBJGroup();
//				currentGroup.name = name;
			}
		}

	}
	obj.groups.push_back(currentGroup);

	return true;
}


Vector3df OBJFileReader::readVertices(const std::vector<std::string>& strs)
{
	const float x = std::stof(strs[1].c_str());
	const float y = std::stof(strs[2].c_str());
	const float z = std::stof(strs[3].c_str());
	if (strs.size() == 5) {
		const float w = ::std::stof(strs[4].c_str());
		return Vector3df(x, y, z);
	}
	else {
		return Vector3df(x, y, z);
	}
}

Vector3df OBJFileReader::readVector3d(const std::vector<std::string>& strs)
{
	const float u = ::std::stof(strs[1]);
	const float v = ::std::stof(strs[2]);
	if (strs.size() == 4) {
		const float w = std::stof(strs[3]);
		return Vector3df(u, v, w);
	}
	else {
		return Vector3df(u, v, 0.0f);
	}
}

Vector2df OBJFileReader::readVector2d(const std::vector<std::string>& strs)
{
	const float u = ::std::stof(strs[1]);
	const float v = ::std::stof(strs[2]);
	return Vector2df(u, v);
}
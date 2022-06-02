#include "OBJSyntaxParser.h"
#include "Helper.h"

using namespace Crystal::IO;

OBJFace OBJSyntaxParser::parseFace(std::vector< std::string >& strs)
{
	OBJFace face;
	for (int i = 1; i < strs.size(); ++i) {
		auto str = strs[i];
		if (str.empty()) {
			continue;
		}
		std::string::size_type pos(str.find("//"));
		if (pos != std::string::npos) {
			str.replace(pos, 2, "/ /");
		}

		std::vector<std::string>& splitted = Helper::split(str, '/');
		const int positionIndex = std::stoi(splitted[0]);
		face.positionIndices.push_back(positionIndex);

		if (splitted.size() >= 2 && splitted[1] != " ") {
			const int texIndex = std::stoi(splitted[1]);
			face.texCoordIndices.push_back(texIndex);
		}
		else {
			face.texCoordIndices.push_back(-1);
		}

		if (splitted.size() >= 3) {
			const int normalIndex = std::stoi(splitted[2]);
			face.normalIndices.push_back(normalIndex);
		}
		else {
			face.normalIndices.push_back(-1);
		}
	}
	return face;
}


OBJFace OBJSyntaxParser::parseFaceLine(const std::string& line)
{
	std::vector< std::string >& strs = Helper::split(line, ' ');
	return parseFace(strs);
}
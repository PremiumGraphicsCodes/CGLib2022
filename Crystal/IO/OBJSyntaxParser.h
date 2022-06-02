#pragma once

#include "OBJFile.h"

namespace Crystal {
	namespace IO {

class OBJSyntaxParser
{
public:
	static OBJFace parseFaceLine(const std::string& line);

private:
	static OBJFace parseFace(std::vector< std::string >& strs);
};

	}
}
#include "ShaderUnit.h"

#include <cassert>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glew.h"

using namespace Crystal::Shader;

namespace {
	std::string getStrFromFile(const std::string& file)
	{
		std::ifstream stream(file);
		if (stream.fail()) {
			assert(false);
			return "";
		}
		std::istreambuf_iterator<char> it(stream);
		std::istreambuf_iterator<char> last;
		return std::string(it, last);
	}
}


ShaderUnit::ShaderUnit(void) :
	id(-1)
{
}

ShaderUnit::~ShaderUnit(void)
{
	clear();
}

void ShaderUnit::clear()
{
	if (id != -1) {
		glDeleteShader(id);
	}
}

bool ShaderUnit::compile(const std::string& source, const ShaderUnit::Stage stage)
{
	clear();
	if (stage == ShaderUnit::Stage::VERTEX) {
		id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (stage == ShaderUnit::Stage::FRAGMENT) {
		id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (stage == ShaderUnit::Stage::GEOMETRY) {
		id = glCreateShader(GL_GEOMETRY_SHADER);
	}
	else if (stage == ShaderUnit::Stage::COMPUTE) {
		id = glCreateShader(GL_COMPUTE_SHADER);
	}
	else {
		assert(false);
		return false;
	}
	const GLchar *strPtr[1];
	strPtr[0] = source.c_str();
	glShaderSource(id, 1, strPtr, NULL);

	glCompileShader(id);

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	GLchar infoLog[2048];
	glGetShaderInfoLog(id, 2048, NULL, infoLog);
	log += infoLog;
	//assert( success != 0 );
	//return ( success != 0 );

	if (success == 0) {
		return false;
	}

	if (glGetError() != GL_NO_ERROR) {
		return false;
	}
	return true;
}

bool ShaderUnit::compileFromFile(const std::string& file, const ShaderUnit::Stage stage)
{
	return compile(::getStrFromFile(file), stage);
}

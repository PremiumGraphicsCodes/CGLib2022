#pragma once

#include <string>

namespace Crystal {
	namespace Shader {

class ShaderUnit
{
public:
	ShaderUnit(void);

	~ShaderUnit(void);

	enum class Stage
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		COMPUTE,
	};

	bool compile(const std::string& source, const ShaderUnit::Stage stage);

	bool compileFromFile(const std::string& file, const ShaderUnit::Stage stage);

	//bool dump(const std::string& filename);

	void clear();

	unsigned int getID() const { return id; }

	std::string getLog() const { return log; }

private:

	unsigned int id;

	std::string log;
};

	}
}
#pragma once

#include "../Util/UnCopyable.h"

#include <vector>
#include <map>
#include <string>

#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"
#include "glew.h"

#include "ShaderUnit.h"
#include "IGLObject.h"

namespace Crystal {
	namespace Shader {
		class VertexBufferObject;
		class TextureObject;

class ShaderObject : IGLObject, private UnCopyable
{
private:

public:
	ShaderObject(void);

	~ShaderObject(void);

	void clear() override;

	bool link(const std::vector<ShaderUnit>& shaders);

	bool build(const std::string& vSource, const std::string& fSource);

	bool buildFromFile(const std::string& vFile, const std::string& fFile);

	void release();

	void findUniformLocation(const std::string& str);

	void findAttribLocation(const std::string& str);

	std::string getLog() const { return log; }

	unsigned int getHandle() const { return handle; }

	unsigned int getUniformLocation(const std::string& str);

	unsigned int getAttribLocation(const std::string& str);

	void bind() {
		glUseProgram(getHandle());
	}

	void unbind()
	{
		glUseProgram(0);
	}

	void enable(GLenum e) {
		glEnable(e);
	}

	void disable(GLenum e) {
		glDisable(e);
	}

	void sendUniform(const std::string& name, const Math::Matrix4df& matrix);

	void sendUniform(const std::string& name, const Math::Vector3df& vector);

	void sendUniform(const std::string& name, const TextureObject& texture, const int slotId);

	void sendUniform(const std::string& name, const int value);

	void sendUniform(const std::string& name, const float value);

	void sendVertexAttribute1df(const std::string& name, const std::vector<float>& data);

	void sendVertexAttribute2df(const std::string& name, const std::vector<float>& data);

	void sendVertexAttribute3df(const std::string& name, const std::vector<float>& data);

	void sendVertexAttribute4df(const std::string& name, const std::vector<float>& data);

	void sendVertexAttribute1di(const std::string& name, const std::vector<int>& data);

	void sendVertexAttribute1di(const std::string& name, const VertexBufferObject& vbo);

	void sendVertexAttribute1df(const std::string& name, const VertexBufferObject& vbo);

	void sendVertexAttribute2df(const std::string& name, const VertexBufferObject& vbo);

	void sendVertexAttribute3df(const std::string& name, const VertexBufferObject& vbo);

	void sendVertexAttribute4df(const std::string& name, const VertexBufferObject& vbo);

	void enableVertexAttribute(const std::string& name);

	void disableVertexAttribute(const std::string& name);

	void enableDepthTest();

	void disableDepthTest();

	void enablePointSprite();

	void disablePointSprite();

	void drawPoints(const int count);

	void drawLines(const std::vector<unsigned int>& indices);

	void drawLines(const int count);

	void drawTriangles(const int count);

	void drawTriangles(const std::vector<unsigned int>& indices);

	void bindOutput(const std::string& name);

	void setLineWidth(const float width);

public:
	//GLuint getHandle() const { return handle; }

	bool isBuildOK() const { return isBuildOk; }

private:
	GLuint handle;

	bool isBuildOk;
	std::string log;
	std::map< std::string, unsigned int > uniformMap;
	std::map< std::string, unsigned int > attribMap;


};


	}
}
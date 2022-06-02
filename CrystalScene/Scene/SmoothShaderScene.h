#pragma once

#include "Crystal/Math/Matrix4d.h"
#include "Crystal/Graphics/Buffer1d.h"
#include "Crystal/Graphics/Buffer2d.h"
#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Graphics/Camera.h"
#include "Crystal/Graphics/Material.h"

#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/SmoothRenderer.h"
#include "MaterialShaderScene.h"
#include "IShaderScene.h"
#include "IMaterialScene.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class SmoothShader;
		class CameraShaderScene;

class SmoothGroupBuffer
{
public:
	Graphics::Material material;
	Shader::TextureObject* texture;
	Graphics::Buffer1d<unsigned int> indices;
};

class SmoothBuffer
{
public:
	SmoothBuffer() :
		matrix(Math::Identity<double>())
	{}

	void addVertex(const Math::Vector3df& position, const Math::Vector3df& normal, const Math::Vector2df& texCoord);

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer3d<float> getNormals() const { return normals; }

	Graphics::Buffer2d<float> getTexCoords() const { return texCoords; }

	void setMatrix(const Math::Matrix4dd& matrix) { this->matrix = matrix; }

	Math::Matrix4dd getMatrix() const { return matrix; }
	
	void addGroup(const SmoothGroupBuffer& group) { this->groups.push_back(group); }

	std::vector<SmoothGroupBuffer> getGroups() const { return groups; }

private:
	Math::Matrix4dd matrix;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
	Graphics::Buffer2d<float> texCoords;

	std::vector<SmoothGroupBuffer> groups;
};


class SmoothShaderScene : public IShaderScene
{
public:
	explicit SmoothShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) override;

	void send(const SmoothBuffer& buffer);

	//void setMaterialBuffer(MaterialShaderScene* buffer) override;

	void sendLight(const int index, const Graphics::PointLight& light);

	void sendAllLights();

	void release(Shader::GLObjectFactory& glFactory) override;

	void render(const Graphics::Camera& camera) override;

	void setShader(Shader::SmoothRenderer* shader) { this->shader = shader; }

private:
	Shader::SmoothRenderer* shader;
	Shader::SmoothRenderer::Buffer rBuffer;
	MaterialShaderScene* materialScene;
	LightShaderScene* lightScene;
	TextureShaderScene* textureScene;
};

	}
}
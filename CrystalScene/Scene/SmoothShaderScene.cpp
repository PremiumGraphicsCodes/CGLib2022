#include "SmoothShaderScene.h"

#include "Crystal/Shader/SmoothRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SmoothShaderScene::SmoothShaderScene(const std::string& name) :
	IShaderScene(name),
	shader(nullptr)
{}

void SmoothBuffer::addVertex(const Vector3df& position, const Vector3df& normal, const Vector2df& texCoord)
{
	positions.add(position);
	normals.add(normal);
	texCoords.add(texCoord);
}

bool SmoothShaderScene::build(GLObjectFactory& glFactory)
{
	rBuffer.position.build();
	rBuffer.normal.build();
	rBuffer.texCoord.build();
//	rBuffer.materialId.build();
	return true;
}

void SmoothShaderScene::release(GLObjectFactory& glFactory)
{
	rBuffer.position.release();
	rBuffer.normal.release();
	rBuffer.texCoord.release();
//	rBuffer.materialId.release();
}

void SmoothShaderScene::send(const SmoothBuffer& buffer)
{
	rBuffer.position.send(buffer.getPositions().get());
	rBuffer.normal.send(buffer.getNormals().get());
	rBuffer.texCoord.send(buffer.getTexCoords().get());

	//rBuffer.count = static_cast<int>( buffer.getPositions().get().size() / 3 );
	rBuffer.matrix = buffer.getMatrix();

	const auto& groups = buffer.getGroups();
	for (auto g : groups) {
		SmoothRenderer::BufferBlock block;
		block.material = g.material;
		block.vertexIndices = g.indices;
		rBuffer.blocks.push_back(block);
	}
}

void SmoothShaderScene::sendLight(const int index, const PointLight& light)
{
	shader->sendLight(index, light);
}

void SmoothShaderScene::sendAllLights()
{
	const auto& lights = this->materialScene->getLights();
	for (auto i = 0; i < lights.size(); ++i) {
		shader->sendLight(i, lights[i]);
	}
}

void SmoothShaderScene::render(const Graphics::Camera& camera)
{
	rBuffer.modelViewMatrix = camera.getModelViewMatrix();
	rBuffer.projectionMatrix = camera.getProjectionMatrix();
	//rBuffer.textures = this->materialScene->getTextures();
	shader->render(rBuffer);
}
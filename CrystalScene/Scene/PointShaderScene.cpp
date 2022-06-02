#include "PointShaderScene.h"

#include "Crystal/Shader/PointRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

PointShaderScene::PointShaderScene(const std::string& name) :
	IShaderScene(name),
	shader(nullptr),
	doBlend(false)
{}

bool PointShaderScene::build(GLObjectFactory& glFactory)
{
	rBuffer.position.build();
	rBuffer.size.build();
	rBuffer.color.build();

	//vao.build();
	return true;
}

void PointShaderScene::release(GLObjectFactory& glFactory)
{
	rBuffer.position.release();
	rBuffer.size.release();
	rBuffer.color.release();

	//vao.release();
}

void PointShaderScene::send(const PointBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();
	const auto& colors = buffer.getColor().get();
	const auto& sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	//vao.bind();
	rBuffer.position.send(positions);
	rBuffer.size.send(sizes);
	rBuffer.color.send(colors);
	//vao.unbind();

	rBuffer.count = static_cast<int>( positions.size() / 3 );
//	rBuffer.matrix = buffer.getMatrix();
}

void PointShaderScene::render(const Graphics::Camera& camera)
{
	if (!isVisible()) {
		return;
	}

	rBuffer.modelViewMatrix = camera.getModelViewMatrix();
	rBuffer.projectionMatrix = camera.getProjectionMatrix();

	if (doBlend) {
		shader->renderBlend(rBuffer);
	}
	else {
		shader->render(rBuffer);
	}
}

void PointShaderScene::setShader(PointRenderer* shader)
{
	this->shader = shader;
}

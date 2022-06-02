
#include "LineShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

LineShaderScene::LineShaderScene(const std::string& name) :
	IShaderScene(name)
{}

bool LineShaderScene::build(GLObjectFactory& glFactory)
{
	sBuffer.position = glFactory.createVertexBufferObject();
	sBuffer.position->build();
	sBuffer.color = glFactory.createVertexBufferObject();
	sBuffer.color->build();

	//vao.build();
	return true;
}

void LineShaderScene::release(GLObjectFactory& glFactory)
{
	sBuffer.position->release();
	sBuffer.color->release();

	//glFactory.vbos.remove(sBuffer.position);
	//glFactory.vbos.remove(sBuffer.color);

	//vao.release();
}

void LineShaderScene::send(const LineBuffer& buffer)
{
	const auto positions = buffer.getPositions().get();
	const auto colors = buffer.getColors().get();

	/*
	if (positions.empty()) {
		return;
	}
	*/

	sBuffer.position->send(positions);
	sBuffer.color->send(colors);

	sBuffer.indices = buffer.getIndices().get();
//	sBuffer.matrix = buffer.getMatrix();
	sBuffer.lineWidth = buffer.getWidth();
}

void LineShaderScene::render(const Camera& camera)
{
	//shader->setScene(this);
	sBuffer.modelViewMatrix = camera.getModelViewMatrix();
	sBuffer.projectionMatrix = camera.getProjectionMatrix();
	shader->render(sBuffer);
}
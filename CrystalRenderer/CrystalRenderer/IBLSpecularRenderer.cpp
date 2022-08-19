#include "IBLSpecularRenderer.h"

using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projection";
	constexpr auto modelMatrixLabel = "model";
	constexpr auto viewMatrixLabel = "view";

	constexpr auto positionLabel = "aPos";
	constexpr auto normalLabel = "aNormal";

	constexpr auto albedoLabel = "albedo";
	constexpr auto metalicLabel = "metallic";
	constexpr auto ambientOcclusionLabel = "ao";
	constexpr auto irradianceMapLabel = "irradianceMap";
	constexpr auto importanceMapLabel = "prefilterMap";
	constexpr auto brdfLutTexLabel = "brdfLUT";

	constexpr auto cameraPosLabel = "camPos";
	constexpr auto fragColorLabel = "FragColor";
}

IBLSpecularRenderer::IBLSpecularRenderer()
{
}

void IBLSpecularRenderer::link()
{
	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::normalLabel);

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelMatrixLabel);
	shader->findUniformLocation(::viewMatrixLabel);

	shader->findUniformLocation(::albedoLabel);
	shader->findUniformLocation(::metalicLabel);
	shader->findUniformLocation(::ambientOcclusionLabel);
	shader->findUniformLocation(::irradianceMapLabel);
	shader->findUniformLocation(::importanceMapLabel);
	shader->findUniformLocation(::brdfLutTexLabel);
	shader->findUniformLocation(::cameraPosLabel);
}

void IBLSpecularRenderer::render()
{
	shader->bind();
	shader->bindOutput(::fragColorLabel);

	buffer.irradianceMapTex->bind(0);
	buffer.importanceMapTex->bind(1);
	buffer.brdfLutTex->bind(2);

	shader->sendUniform(::irradianceMapLabel, 0);
	shader->sendUniform(::importanceMapLabel, 1);
	shader->sendUniform(::brdfLutTexLabel, 2);

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelMatrixLabel, buffer.modelMatrix);
	shader->sendUniform(::viewMatrixLabel, buffer.viewMatrix);
	shader->sendUniform(::cameraPosLabel, buffer.eyePosition);

	shader->sendVertexAttribute3df(::positionLabel, *buffer.position);
	shader->sendVertexAttribute3df(::normalLabel, *buffer.normal);

	shader->sendUniform(::albedoLabel, buffer.albedo);
	shader->sendUniform(::metalicLabel, buffer.metalic);
	shader->sendUniform(::ambientOcclusionLabel, buffer.ao);

	buffer.position->bind();
	buffer.normal->bind();
	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);

	shader->drawTriangles(buffer.indices);

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::normalLabel);

	buffer.position->unbind();
	buffer.normal->unbind();

	buffer.irradianceMapTex->unbind();
	buffer.importanceMapTex->unbind();

	shader->unbind();
}
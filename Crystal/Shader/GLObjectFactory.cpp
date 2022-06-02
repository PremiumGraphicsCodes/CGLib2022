#include "GLObjectFactory.h"

#include "TextureObject.h"
#include "FrameBufferObject.h"
#include "VertexBufferObject.h"
#include "ShaderObject.h"

using namespace Crystal::Shader;

GLObjectFactory::~GLObjectFactory()
{
	clear();
}

void GLObjectFactory::clear()
{
	textures.clear();
	shaders.clear();
	vbos.clear();
	fbos.clear();
}

FrameBufferObject* GLObjectFactory::createFrameBufferObject()
{
	auto fbo = std::make_unique<FrameBufferObject>();
	fbos.push_back(std::move(fbo));
	return fbos.back().get();
}

VertexBufferObject* GLObjectFactory::createVertexBufferObject()
{
	auto vbo = std::make_unique<VertexBufferObject>();
	vbos.push_back(std::move(vbo));
	return vbos.back().get();
}

ShaderObject* GLObjectFactory::createShaderObject()
{
	auto shader = std::make_unique<ShaderObject>();
	shaders.push_back(std::move(shader));
	return shaders.back().get();
}

TextureObject* GLObjectFactory::createTextureObject()
{
	auto texture = std::make_unique<TextureObject>();
	texture->create("");
	textures.push_back(std::move(texture));
	return textures.back().get();
}

void GLObjectFactory::remove(FrameBufferObject* fbo)
{
	fbos.remove_if( [fbo](auto& o) { return o.get() == fbo; });
}

void GLObjectFactory::remove(VertexBufferObject* vbo)
{
	vbos.remove_if([vbo](auto& o) { return o.get() == vbo; });
}

void GLObjectFactory::remove(TextureObject* texture)
{
	textures.remove_if([texture](auto& o) { return o.get() == texture; });
}

void GLObjectFactory::remove(ShaderObject* shader)
{
	shaders.remove_if([shader](auto& s) { return s.get() == shader; });
}

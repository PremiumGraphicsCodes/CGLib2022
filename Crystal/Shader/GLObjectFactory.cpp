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
	objects.clear();
}

FrameBufferObject* GLObjectFactory::createFrameBufferObject()
{
	auto fbo = std::make_unique<FrameBufferObject>();
	objects.push_back(std::move(fbo));
	return static_cast<FrameBufferObject*>( objects.back().get() );
}

VertexBufferObject* GLObjectFactory::createVertexBufferObject()
{
	auto vbo = std::make_unique<VertexBufferObject>();
	objects.push_back(std::move(vbo));
	return static_cast<VertexBufferObject*>( objects.back().get() );
}

ShaderObject* GLObjectFactory::createShaderObject()
{
	auto shader = std::make_unique<ShaderObject>();
	objects.push_back(std::move(shader));
	return static_cast<ShaderObject*>( objects.back().get() );
}

TextureObject* GLObjectFactory::createTextureObject()
{
	auto texture = std::make_unique<TextureObject>();
	texture->create("");
	objects.push_back(std::move(texture));
	return static_cast<TextureObject*>( objects.back().get() );
}

void GLObjectFactory::add(IGLObject* object)
{
	std::unique_ptr<IGLObject> obj(object);
	//auto obj = std::make_unique<IGLObject>(object);
	objects.push_back(std::move(obj));
}

void GLObjectFactory::remove(IGLObject* fbo)
{
	objects.remove_if( [fbo](auto& o) { return o.get() == fbo; });
}
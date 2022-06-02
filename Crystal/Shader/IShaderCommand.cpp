#include "IShaderCommand.h"

#include "ShaderObject.h"

using namespace Crystal::Shader;

void SendVertexAttribute3dfCommand::execute(ShaderObject* shader)
{
	shader->sendVertexAttribute3df("position", positions);
}

void EnableVertexAttributeCommand::execute(ShaderObject* shader)
{
	shader->enableVertexAttribute(name);
}

#include "PBLightShader.h"

#include "CrystalScene/Scene/PolygonRenderer.h"

#include "Crystal/Shader/FrameBufferObject.h"
#include "Crystal/Shader/TextureObject.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

ShaderBuildStatus PBLightShader::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	status.add(renderer.build(factory));

	positions.add(Vector3dd(0.0, 0.0, 0.0));
	positions.add(Vector3dd(1.0, 0.0, 0.0));
	positions.add(Vector3dd(1.0, 1.0, 0.0));
	positions.add(Vector3dd(0.0, 1.0, 0.0));

	normals.add(Vector3dd(0, 0, 1));
	normals.add(Vector3dd(0, 0, 1));
	normals.add(Vector3dd(0, 0, 1));
	normals.add(Vector3dd(0, 0, 1));

	buffer.position.build();
	buffer.normal.build();

	buffer.position.send(positions.get());
	buffer.normal.send(normals.get());

	buffer.indices.push_back(0);
	buffer.indices.push_back(1);
	buffer.indices.push_back(2);

	buffer.indices.push_back(0);
	buffer.indices.push_back(2);
	buffer.indices.push_back(3);

	buffer.lightPosition = Vector3dd(1, 1, 1);
	buffer.lightColor = Vector3dd(1, 1, 1);
	
	buffer.albedo = Vector3dd(1, 1, 1);
	buffer.roughness = 0.1;
	buffer.metalic = 0.1;
	buffer.ao = 0.1;

	return status;
}

void PBLightShader::release(GLObjectFactory& factory)
{
	buffer.position.release();
	buffer.normal.release();
}

void PBLightShader::render(const Camera& camera, const int width, const int height)
{

	{

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		buffer.modelMatrix = camera.getModelMatrix();
		buffer.viewMatrix = camera.getViewMatrix();
		buffer.projectionMatrix = camera.getProjectionMatrix();
		buffer.eyePosition = camera.getEye();

		this->renderer.render(buffer);
	}
}

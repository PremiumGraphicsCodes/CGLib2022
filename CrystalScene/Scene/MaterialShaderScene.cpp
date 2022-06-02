#include "MaterialShaderScene.h"

#include "IMaterialScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void MaterialShaderScene::updateMaterial(const int index)
{
	for (auto s : parentScenes) {
		s->sendMaterial(index, materials[index]);
	}
}

void MaterialShaderScene::updateLight(const int index)
{
	for (auto s : parentScenes) {
		s->sendLight(index, lights[index]);
	}
}

void MaterialShaderScene::updateTexture(const int index)
{
	for (auto s : parentScenes) {
		s->sendTexture(index, *textures[index]);
	}
}
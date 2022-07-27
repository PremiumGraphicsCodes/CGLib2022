#include "World.h"

#include "PointShaderScene.h"
#include "LightScene.h"
#include "MaterialScene.h"
#include "TextureScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

World::World() :
	sceneIdProvider(1)
{
	scene = std::make_unique<Scene>(0, "Root");
	//createDefaultCamera();
}

World::~World()
{
	clear();
}

void World::init()
{
	renderer = std::make_unique<SceneShader>();

	{
		auto light = std::make_unique<PointLight>();
		light->setPosition(Vector3dd(100, 100, 100));
		light->setAmbient(ColorRGBAf(1, 1, 1, 1));
		light->setDiffuse(ColorRGBAf(1, 1, 1, 1));
		light->setSpecular(ColorRGBAf(1, 1, 1, 1));
		auto s = new LightScene(getNextSceneId(), "Light0", std::move(light));
		//s->getPresenter()->createView(renderer.get(), glFactory);
		scene->addScene(s);
		//scenes[1]->addScene(sceneFactory.createLightScene(std::move(light), "Light0"));
	}

	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(1, 1, 1, 1);
		material->diffuse = ColorRGBAf(1, 1, 1, 1);
		material->specular = ColorRGBAf(1, 1, 1, 1);
		material->shininess = 1.0;
		auto s = new MaterialScene(getNextSceneId(), "WhiteMat", std::move(material));
		//s->getPresenter()->createView(renderer.get(), glFactory);
		scene->addScene(s);
	}

	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(1, 0, 0, 1);
		material->diffuse = ColorRGBAf(0, 0, 0, 1);
		material->specular = ColorRGBAf(0, 0, 0, 1);
		material->shininess = 1.0;
		auto s = new MaterialScene(getNextSceneId(),"RedMat", std::move(material));
		//s->getPresenter()->createView(renderer.get(), glFactory);
		scene->addScene(s);
	}

	{
		auto material = std::make_unique<Material>();
		material->ambient = ColorRGBAf(0, 0, 0, 1);
		material->diffuse = ColorRGBAf(0, 0, 0, 1);
		material->specular = ColorRGBAf(0, 0, 0, 1);
		material->shininess = 1.0;
		auto s = new MaterialScene(getNextSceneId(), "BlackMat", std::move(material));
		//s->getPresenter()->createView(renderer.get(), glFactory);
		scene->addScene(s);
	}

	{
		auto image = std::make_unique<Image>(2,2);
		image->setColor(0, 0, ColorRGBAuc(255, 0, 0, 255));
		image->setColor(0, 1, ColorRGBAuc(0, 255, 0, 255));
		image->setColor(1, 0, ColorRGBAuc(0, 255, 255, 255));
		image->setColor(1, 1, ColorRGBAuc(0, 0, 0, 255));

		auto s = new TextureScene(getNextSceneId(), std::move(image), "WhiteTex");
		//s->getPresenter()->createView(renderer.get(), glFactory);
		scene->addScene(s);
	}

	{
		auto image = std::make_unique<Image>(1, 1);
		image->setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
		auto s = new TextureScene(getNextSceneId(), std::move(image), "BlackTex");
		//s->getPresenter()->createView(renderer.get(), glFactory);
		scene->addScene(s);
	}

	//renderer = std::make_unique<SceneShader>();

}

int World::createDefaultCamera()
{
	auto c = new Camera(
			Vector3df(0, 0, 0),
			Vector3df(0, 0, -10.0),
			Vector3df(0, 1, 0),
			1.0f, 10.0f);
	camera = new CameraScene(getNextSceneId(), "MainCamera", c);

	scene->addScene(camera);
	return camera->getId();
}

void World::clear()
{
	//glFactory.clear();
	sceneIdProvider.reset(1);
	scene->clear();
	animations.clear();
}

void World::addScene(IScene* scene)
{
	this->scene->addScene(scene);
}

Box3dd World::getBoundingBox() const
{
	return scene->getBoundingBox();
}

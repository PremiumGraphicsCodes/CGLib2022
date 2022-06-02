#include "MaterialView.h"

#include "../Scene/MaterialScene.h"
#include "../Scene/TextureScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialView::MaterialView(const std::string& name) :
	IView(name),
	ambientView("Ambient", glm::vec4(0, 0, 0, 0)),
	diffuseView("Diffuse", glm::vec4(0, 0, 0, 0)),
	specularView("Specular", glm::vec4(0, 0, 0, 0)),
	shininessView("Shininess", 1.0f),
	ambientTextureNameView("AmbientTexture"),
	diffuseTextureNameView("DiffuseTexture"),
	specularTextureNameView("SpecularTexture")
{
	add(&ambientView);
	add(&diffuseView);
	add(&specularView);
	add(&shininessView);
	add(&ambientTextureNameView);
	add(&diffuseTextureNameView);
	add(&specularTextureNameView);
}

void MaterialView::setValue(const Material& m)
{
	ambientView.setValue(m.ambient);
	diffuseView.setValue(m.diffuse);
	specularView.setValue(m.specular);
	shininessView.setValue(m.shininess);

	ambientTextureNameView.setValue(m.ambientTexName);
	diffuseTextureNameView.setValue(m.diffuseTexName);
	specularTextureNameView.setValue(m.specularTexName);
}

Material MaterialView::getValue() const
{
	Material m;
	m.ambient = ambientView.getValue();
	m.diffuse = diffuseView.getValue();
	m.specular = specularView.getValue();
	m.shininess = shininessView.getValue();

	m.ambientTexName = ambientTextureNameView.getValue();
	m.diffuseTexName = diffuseTextureNameView.getValue();
	m.specularTexName = specularTextureNameView.getValue();
	return m;
}

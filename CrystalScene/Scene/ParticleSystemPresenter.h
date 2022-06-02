#pragma once

#include "IParticleSystemPresenter.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;

class ParticleSystemPresenter : public IParticleSystemPresenter
{
public:
	explicit ParticleSystemPresenter(ParticleSystemScene* model);

	void createView(SceneShader* sceneShader) override;

	void removeView(SceneShader* sceneShader) override;

	void updateView() override;

	void setBlend(const bool b) { this->doBlend = b; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	PointShaderScene* view;
	PointShaderScene* parentIdView;
	PointShaderScene* childIdView;
	bool doBlend;
};

	}
}
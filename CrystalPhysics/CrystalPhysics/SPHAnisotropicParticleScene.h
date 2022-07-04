#pragma once

#include "CrystalScene/Scene/IScene.h"
//#include "FluidVolumePresenter.h"
#include "SurfaceConstruction/SPHAnisotoropicParticle.h"

namespace Crystal {
	namespace Physics {

		class SPHAnisotropicParticleScene : public Scene::IScene
		{
		public:
			SPHAnisotropicParticleScene(const int id, const std::string& name, std::unique_ptr<Space::SparseVolumef> shape);

			//virtual ~FluidVolumeScene();

			//Space::SparseVolumef* getShape() const { return shape.get(); }

			//void resetShape(std::unique_ptr<Space::SparseVolumef> shape) { this->shape = std::move(shape); }

			Scene::SceneType getType() const { return Scene::SceneType("SPHAnisotoropicParticleScene"); }

			Scene::IPresenter* getPresenter() { return presenter.get(); }

			Math::Box3dd getBoundingBox() const override;


		private:
			//std::unique_ptr<FluidVolumePresenter> presenter;
			//std::unique_ptr<Space::SparseVolumef> shape;
		};


	}
}
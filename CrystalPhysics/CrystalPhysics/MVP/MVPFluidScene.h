#pragma once

#include "IMVPFluidScene.h"

namespace Crystal {
	namespace Physics {

class MVPFluidScene : public IMVPFluidScene
{
public:
	MVPFluidScene(const int id, const std::string& name);

	~MVPFluidScene() = default;

	static constexpr auto Type = "KFFluid";

	Scene::SceneType getType() const { return Type; }

	bool isBoundary() const { return isBoundary_; }

	void setBoundary(const bool isBoundary_) { this->isBoundary_ = isBoundary_; }

private:
	bool isBoundary_;
};


	}
}

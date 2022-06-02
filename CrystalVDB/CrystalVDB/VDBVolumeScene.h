#pragma once

#include <memory>

#include "../../CrystalScene/Scene/IShapeScene.h"

#include "../../Crystal/Math/Box3d.h"

#include "VDBVolumePresenter.h"

namespace Crystal {
	namespace VDB {
		class VDBVolumeImpl;

class VDBVolumeScene : public Scene::IShapeScene
{
public:
	VDBVolumeScene();

	//explicit VDBVolumeScene(VDBVolumeImpl* impl);

	explicit VDBVolumeScene(const float value);

	VDBVolumeScene(const int id, const std::string& name);

	//void setImpl(VDBVolumeImpl* impl) { this->impl = impl; }

	//explicit Volume(std::unique_ptr<VolumeImpl> impl);

	void setValue(const std::array<int,3>& index, const float value);

	float getValue(const std::array<int, 3> index);

	~VDBVolumeScene();

	void fill(const unsigned int coord1, const unsigned int coord2, const float value);

	int getActiveVoxelCount() const;

	void translate(const Math::Vector3dd& v) override {};

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	Scene::IPresenter* getPresenter() { return presenter.get(); };

	static constexpr auto Type = "VDBVolume";

	Scene::SceneType getType() const { return Type; }

	Math::Box3dd getBoundingBox() const override;

	VDBVolumeImpl* getImpl() const { return impl.get(); }

	void setScale(const double scale);

	void resetImpl();

private:
	std::unique_ptr<VDBVolumeImpl> impl;
	std::unique_ptr<VDBVolumePresenter> presenter;
};
	}
}
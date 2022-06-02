#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Util/UnCopyable.h"

#include "../../CrystalScene/Scene/IParticleSystemScene.h"
#include "VDBPointsPresenter.h"

#include <memory>

namespace Crystal {
    namespace VDB {
        class VDBPointsImpl;

class VDBPointsScene : public Scene::IParticleSystemScene
{
public:
    VDBPointsScene();

    VDBPointsScene(const int id, const std::string name);

    ~VDBPointsScene();

    void create(const std::vector<Math::Vector3dd>& positions);

    VDBPointsImpl* getImpl() const { return impl.get(); }

    void translate(const Math::Vector3dd& v) override {};

    void transform(const Math::Matrix3dd& m) override {};

    void transform(const Math::Matrix4dd& m) override {};

    Scene::IPresenter* getPresenter() { return presenter.get(); };

    static constexpr auto Type = "VDBParticleSystem";

    Scene::SceneType getType() const { return Type; }

    Math::Box3dd getBoundingBox() const override;

    std::vector<Math::Vector3dd> getPositions() const override;

    void resetImpl();

    void addFloatAttribute(const std::string& name);

    void setFloatAttribute(const std::string& name, const std::vector<float>& values);

    std::vector<float> getFloatAttribute(const std::string& name);

    bool hasAttribute(const std::string& name);

    std::vector<std::string> getAttributeNames() const;

    std::vector<std::string> getFloatAttributeNames() const;

private:
    std::unique_ptr<VDBPointsImpl> impl;
    std::unique_ptr<VDBPointsPresenter> presenter;
};

    }
}
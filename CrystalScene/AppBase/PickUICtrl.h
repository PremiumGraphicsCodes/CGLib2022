#include <memory>
#include "../../Crystal/Graphics/Camera.h"
#include "Canvas.h"
#include "IUICtrl.h"

#include "../Scene/SceneType.h"

#include <functional>

namespace Crystal {
	namespace Scene {
		class World;
	}
	namespace UI {

class PickUICtrl : public IUICtrl
{
public:
	PickUICtrl(Scene::World* model, Canvas* canvas, const Scene::SceneType& type, const float mergin);

	virtual ~PickUICtrl() {}

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float dx) override;

	void setFunction(const std::function<void(int, int)>& func) { this->function = func; }

private:
	Scene::World* model;
	Canvas* canvas;
	std::function<void(int, int)> function;
	const Scene::SceneType type;
	float mergin;
};
	}
}

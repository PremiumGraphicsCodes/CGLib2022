#include "SphereRegionSelectView.h"
#include "PickUICtrl.h"
#include "CameraUICtrl.h"

#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../Scene/IShapeScene.h"
#include "../Scene/WireFrameScene.h"

#include "imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

/*
void SphereRegionSelectView::onShow()
{
	if (ImGui::Button("Pick")) {
		auto mask = (int)SceneType::ParticleSystemScene | (int)SceneType::WireFrameScene | (int)SceneType::PolygonMeshScene;
		auto ctrl = new PickUICtrl(getWorld(), getCanvas(), SceneType(mask));
		auto model = getWorld();
		auto canvas = getCanvas();

		auto func = [=](int parentId, int childId) {
			auto scene = model->getObjects()->findSceneById<IShapeScene*>(parentId);
			const auto& position = scene->getPosition(childId);
			auto s = sphere.getValue();
			s.moveTo(position);
			sphere.setValue(s);

			WireFrameBuilder builder;
			builder.build(s, 36, 36);
			WireFrameAttribute attr;
			attr.color = Graphics::ColorRGBAf(1.0, 0.0, 0.0, 0.0);
			attr.width = 1.0;

			model->getItems()->addScene( model->getItemFactory()->createWireFrameScene(builder.getWireFrame(), attr, "Region") );
			model->updateViewModel();
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}

	sphere.show();
}
*/
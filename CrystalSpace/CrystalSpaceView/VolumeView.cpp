#include "VolumeView.h"

#include "../../Crystal/Graphics/ColorMap.h"
#include "../../Crystal/Graphics/ColorHSV.h"

#include "CrystalScene/Scene/VolumeScene.h"
#include "CrystalScene/Scene/ParticleAttribute.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::UI;

VolumeView::VolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	box("Box")
{
}

void VolumeView::onShow()
{
	box.show();
}

void VolumeView::onOk()
{
	std::array<size_t, 3> resolutions{ 32,32,32 };
	Volume<double> volume(box.getValue(), resolutions);

	/*
	auto function = [](double distance) {
		Gaussian gaussian;
		return gaussian.getValue(distance);
	};
	volume.add(function);

	/*
	const auto& particles = volume.toParticles();
	std::vector<double> values;
	for (const auto& p : particles) {
		values.push_back(p.getAttribute());
	}
	const auto minValue = *std::min_element(values.begin(), values.end());
	const auto maxValue = *std::max_element(values.begin(), values.end());

	ColorMap colorMap(minValue, maxValue, 360);
	for (int i = 0; i < 360; ++i) {
		ColorHSV hsv(i, 1.0, 1.0);
		colorMap.setColor(i, hsv.toColorRGBA());
	}

	std::vector<Vector3dd> positions;
	std::vector<ParticleAttribute> attrs;
	for (const auto& p : particles) {
		positions.push_back(p.getPosition());
		const auto value = p.getAttribute();
		ParticleAttribute attr;
		attr.color = colorMap.getColor(value);
		attr.size = 1.0;
		attrs.push_back(attr);
	}

	getWorld()->getObjectFactory()->createParticleSystemScene(positions, attrs, "VolumeConverter");
	getWorld()->updateViewModel();
	*/
}

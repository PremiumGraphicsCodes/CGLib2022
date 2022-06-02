#include "WireFrameCreateCommand.h"

#include "../Scene/WireFrameAttribute.h"
#include "../Scene/WireFrameScene.h"

#include "Crystal/Shape/WireFrameBuilder.h"

#include "PublicLabel.h"

namespace WireFrameCreateLabels
{
	PublicLabel WireFrameCreateLabel = "WireFrameCreate";
	PublicLabel PositionsLabel = "Positions";
	PublicLabel EdgeIndicesLabel = "EdgeIndices";
	PublicLabel LineWidthLabel = "LineWidth";
	PublicLabel ColorLabel = "Color";
	PublicLabel NameLabel = "Name";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

WireFrameCreateCommand::Args::Args() :
	positions(WireFrameCreateLabels::PositionsLabel, {}),
	edgeIndices(WireFrameCreateLabels::EdgeIndicesLabel, {}),
	lineWidth(WireFrameCreateLabels::LineWidthLabel, 1.0f),
	color(WireFrameCreateLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(WireFrameCreateLabels::NameLabel, std::string(""))
{
	add(&positions);
	add(&edgeIndices);
	add(&lineWidth);
	add(&color);
	add(&name);
}

WireFrameCreateCommand::Results::Results() :
	newId(WireFrameCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string WireFrameCreateCommand::getName()
{
	return WireFrameCreateLabels::WireFrameCreateLabel;
}

bool WireFrameCreateCommand::execute(World* world)
{
	const auto& positions = args.positions.getValue();
	const auto& edgeIndices = args.edgeIndices.getValue();
	WireFrameAttribute attr;
	attr.color = args.color.getValue();
	attr.width = args.lineWidth.getValue();
	const auto& name = args.name.getValue();

	std::vector<WireFrameEdge> edges;
	for (int i = 0; i < edgeIndices.size(); i+=2) {
		const auto startIndex = edgeIndices[i];
		const auto endIndex = edgeIndices[i + 1];
		edges.emplace_back(startIndex, endIndex);
	}
	auto shape = std::make_unique<WireFrame>(positions, edges);
	auto newId = world->getNextSceneId();
	auto scene = new WireFrameScene(newId, name, std::move(shape), attr);
	world->getScenes()->addScene(scene);
	//world->addScene(args.layer.getValue(), scene);
	results.newId.setValue(scene->getId());
	//world->updateViewModel();
	return true;
}

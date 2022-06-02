#include "PickCommand.h"

#include "PublicLabel.h"

namespace PickLabels
{
	PublicLabel PickCommandLabel = "Pick";
	PublicLabel PositionLabel = "Position";
	PublicLabel ParentIdLabel = "ParentId";
	PublicLabel ChildIdLabel = "ChildId";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PickCommand::Args::Args() :
	position(PickLabels::PositionLabel, Vector2dd())
{
	add(&position);
}

PickCommand::Results::Results() :
	parentId(PickLabels::ParentIdLabel, -1),
	childId(PickLabels::ChildIdLabel,-1)
{
	add(&parentId);
	add(&childId);
}

std::string PickCommand::getName()
{
	return PickLabels::PickCommandLabel;
}

bool PickCommand::execute(World* world)
{
	const auto& p = args.position.getValue();
	const auto parentId = world->getRenderer()->getParentIdRenderer()->getId(p.x, p.y);
	results.parentId.setValue( parentId.getId() );
//	results.childId.setValue( id.getChildId() );
	return true;
}


#include "TransformView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TransformView::TransformView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	objectSelectView("Object", model, canvas),
	matrixView("Matrix", glm::identity<Matrix4dd>())
{
	add(&objectSelectView);
	add(&matrixView);
}

void TransformView::onOk()
{
	/*
	Crystal::Command::Command command(::TransformLabels::TransformCommandLabel);
	command.setArg(::TransformLabels::IdLabel, objectSelectView.getId());
	command.setArg(::TransformLabels::MatrixLabel, matrixView.getValue());
	command.execute(getWorld());

	command.create(::ShaderSendLabels::CommandNameLabel);
	command.setArg(::ShaderSendLabels::IdLabel, objectSelectView.getId());
	command.execute(getWorld());
	*/
}

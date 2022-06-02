#include "DeleteView.h"

#include "../Command/DeleteCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

DeleteView::DeleteView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	idView("Id", -1)

{
	add(&idView);
}

void DeleteView::onOk()
{
	/*
	Command::Command command(DeleteLabels::CommandNameLabel);
	command.setArg(DeleteLabels::IdLabel, idView.getValue());
	command.execute(getWorld());
	*/
}
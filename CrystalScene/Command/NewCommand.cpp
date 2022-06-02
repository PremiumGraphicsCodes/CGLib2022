#include "NewCommand.h"

#include "PublicLabel.h"

namespace NewLabels
{
	PublicLabel CommandNameLabel = "NewCommand";
}

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string NewCommand::getName()
{
	return ::NewLabels::CommandNameLabel;
}

bool NewCommand::execute(World* model)
{
	model->clear();
	model->init();
	model->getRenderer()->build();

	//world->getRenderer()->build(*world->getGLFactory());
	//model->getCamera()->getPresenter()->createView(model->getRenderer(), *model->getGLFactory());

//	model->updateViewModel();

	return true;
}

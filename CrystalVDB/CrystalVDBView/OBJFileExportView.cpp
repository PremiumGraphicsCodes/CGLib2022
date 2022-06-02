#include "OBJFileExportView.h"

//#include "../VDBCommand/VDBOBJFileWriteCommand.h"

using namespace Crystal::UI;
//using namespace Crystal::VDB;

OBJFileExportView::OBJFileExportView(const std::string& name, Scene::World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	vdbMeshSelectView("VDBMesh", model, canvas),
	fileSaveView("OBJFile")
{
	add(&vdbMeshSelectView);
	add(&fileSaveView);
	fileSaveView.addFilter("obj");
}

void OBJFileExportView::onOk()
{
	/*
	VDBOBJFileWriteCommand::Args args;
	args.vdbMeshId.setValue( vdbMeshSelectView.getId() );
	args.filePath.setValue( fileSaveView.getFileName() );
	VDBOBJFileWriteCommand command(args);
	command.execute(getWorld());
	*/
}
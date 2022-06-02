#include "CommandFactory.h"

#include "MockCommand.h"
#include "NewCommand.h"
#include "CameraCreateCommand.h"
#include "FileImportCommand.h"
#include "FileExportCommand.h"
#include "ParticleSystemCreateCommand.h"
#include "ParticleSystemGetCommand.h"
#include "ParticleSystemSetCommand.h"
#include "WireFrameCreateCommand.h"
#include "PolygonMeshCreateCommand.h"
#include "PolygonMeshAddVerticesCommand.h"
#include "PolygonMeshAddFacesCommand.h"
#include "TriangleMeshCreateCommand.h"
#include "TriangleMeshGetCommand.h"
#include "TriangleMeshSetCommand.h"
#include "SolidCreateCommand.h"
#include "CameraFitCommand.h"
#include "CameraTranslateCommand.h"
#include "CameraRotateCommand.h"
#include "CameraZoomCommand.h"
#include "PickCommand.h"
#include "TransformCommand.h"
#include "TrimCommand.h"
#include "LightCreateCommand.h"
#include "LightSetCommand.h"
#include "LightGetCommand.h"
#include "MaterialCreateCommand.h"
#include "MaterialGetCommand.h"
#include "MaterialSetCommand.h"
#include "TextureCreateCommand.h"
#include "TextureSetCommand.h"
#include "ShapeSelectCommand.h"
#include "DeleteCommand.h"
#include "ClearCommand.h"
#include "OBJFileImportCommand.h"
#include "STLFileImportCommand.h"
#include "PCDFileImportCommand.h"
#include "PLYFileImportCommand.h"
#include "TXTFileImportCommand.h"
#include "OBJFileExportCommand.h"
#include "STLFileExportCommand.h"
#include "PCDFileExportCommand.h"
#include "PLYFileExportCommand.h"
#include "TXTFileExportCommand.h"
#include "SceneGetCommand.h"
#include "SceneSetCommand.h"
#include "CameraGetCommand.h"
#include "CameraSetCommand.h"
#include "ShaderBuildCommand.h"
#include "ShaderSendCommand.h"
#include "PresenterSetCommand.h"

using namespace Crystal::Command;

std::unique_ptr<ICommand> CommandFactory::create(const std::string& name)
{
	if (name == MockCommand::getName()) {
		return std::make_unique<MockCommand>();
	}
	else if (name == NewCommand::getName()) {
		return std::make_unique<NewCommand>();
	}
	else if (name == CameraCreateCommand::getName()) {
		return std::make_unique<CameraCreateCommand>();
	}
	else if (name == FileImportCommand::getName()) {
		return std::make_unique<FileImportCommand>();
	}
	else if (name == FileExportCommand::getName()) {
		return std::make_unique<FileExportCommand>();
	}
	else if (name == ParticleSystemCreateCommand::getName()) {
		return std::make_unique<ParticleSystemCreateCommand>();
	}
	else if (name == ParticleSystemGetCommand::getName()) {
		return std::make_unique<ParticleSystemGetCommand>();
	}
	else if (name == ParticleSystemSetCommand::getName()) {
		return std::make_unique<ParticleSystemSetCommand>();
	}
	else if (name == WireFrameCreateCommand::getName()) {
		return std::make_unique<WireFrameCreateCommand>();
	}
	else if (name == PolygonMeshCreateCommand::getName()) {
		return std::make_unique<PolygonMeshCreateCommand>();
	}
	else if (name == PolygonMeshAddVerticesCommand::getName()) {
		return std::make_unique<PolygonMeshAddVerticesCommand>();
	}
	else if (name == PolygonMeshAddFacesCommand::getName()) {
		return std::make_unique<PolygonMeshAddFacesCommand>();
	}
	else if (name == TriangleMeshCreateCommand::getName()) {
		return std::make_unique<TriangleMeshCreateCommand>();
	}
	else if (name == TriangleMeshGetCommand::getName()) {
		return std::make_unique<TriangleMeshGetCommand>();
	}
	else if (name == TriangleMeshSetCommand::getName()) {
		return std::make_unique<TriangleMeshSetCommand>();
	}
	else if (name == SolidCreateCommand::getName()) {
		return std::make_unique<SolidCreateCommand>();
	}
	else if (name == CameraFitCommand::getName()) {
		return std::make_unique<CameraFitCommand>();
	}
	else if (name == CameraXYCommand::getName()) {
		return std::make_unique<CameraXYCommand>();
	}
	else if (name == CameraYZCommand::getName()) {
		return std::make_unique<CameraYZCommand>();
	}
	else if (name == CameraZXCommand::getName()) {
		return std::make_unique<CameraZXCommand>();
	}
	else if (name == CameraTranslateCommand::getName()) {
		return std::make_unique<CameraTranslateCommand>();
	}
	else if (name == CameraRotateCommand::getName()) {
		return std::make_unique<CameraRotateCommand>();
	}
	else if (name == CameraZoomCommand::getName()) {
		return std::make_unique<CameraZoomCommand>();
	}
	else if (name == PickCommand::getName()) {
		return std::make_unique<PickCommand>();
	}
	else if (name == TransformCommand::getName()) {
		return std::make_unique<TransformCommand>();
	}
	else if (name == TrimCommand::getName()) {
		return std::make_unique<TrimCommand>();
	}
	else if (name == LightCreateCommand::getName()) {
		return std::make_unique<LightCreateCommand>();
	}
	else if (name == MaterialCreateCommand::getName()) {
		return std::make_unique<MaterialCreateCommand>();
	}
	else if (name == TextureCreateCommand::getName()) {
		return std::make_unique<TextureCreateCommand>();
	}
	else if (name == TextureSetCommand::getName()) {
		return std::make_unique<TextureSetCommand>();
	}
	else if (name == ShapeSelectCommand::getName()) {
		return std::make_unique<ShapeSelectCommand>();
	}
	else if (name == DeleteCommand::getName()) {
		return std::make_unique<DeleteCommand>();
	}
	else if (name == ClearCommand::getName()) {
		return std::make_unique<ClearCommand>();
	}
	else if (name == OBJFileImportCommand::getName()) {
		return std::make_unique<OBJFileImportCommand>();
	}
	else if (name == STLFileImportCommand::getName()) {
		return std::make_unique<STLFileImportCommand>();
	}
	else if (name == PCDFileImportCommand::getName()) {
		return std::make_unique<PCDFileImportCommand>();
	}
	else if (name == PLYFileImportCommand::getName()) {
		return std::make_unique<PLYFileImportCommand>();
	}
	else if (name == TXTFileImportCommand::getName()) {
		return std::make_unique<TXTFileImportCommand>();
	}
	else if (name == OBJFileExportCommand::getName()) {
		return std::make_unique<OBJFileExportCommand>();
	}
	else if (name == STLFileExportCommand::getName()) {
		return std::make_unique<STLFileExportCommand>();
	}
	else if (name == PCDFileExportCommand::getName()) {
		return std::make_unique<PCDFileExportCommand>();
	}
	else if (name == PLYFileExportCommand::getName()) {
		return std::make_unique<PLYFileExportCommand>();
	}
	else if (name == TXTFileExportCommand::getName()) {
		return std::make_unique<TXTFileExportCommand>();
	}
	else if (name == LightSetCommand::getName()) {
		return std::make_unique<LightSetCommand>();
	}
	else if (name == LightGetCommand::getName()) {
		return std::make_unique<LightGetCommand>();
	}
	else if (name == MaterialSetCommand::getName()) {
		return std::make_unique<MaterialSetCommand>();
	}
	else if (name == MaterialGetCommand::getName()) {
		return std::make_unique<MaterialGetCommand>();
	}
	else if (name == SceneGetCommand::getName()) {
		return std::make_unique<SceneGetCommand>();
	}
	else if (name == SceneSetCommand::getName()) {
		return std::make_unique<SceneSetCommand>();
	}
	else if (name == CameraGetCommand::getName()) {
		return std::make_unique<CameraGetCommand>();
	}
	else if (name == CameraSetCommand::getName()) {
		return std::make_unique<CameraSetCommand>();
	}
	else if (name == ShaderBuildCommand::getName()) {
		return std::make_unique<ShaderBuildCommand>();
	}
	else if (name == ShaderSendCommand::getName()) {
		return std::make_unique<ShaderSendCommand>();
	}
	else if (name == PresenterSetCommand::getName()) {
		return std::make_unique<PresenterSetCommand>();
	}

	assert(false);
	return nullptr;
}
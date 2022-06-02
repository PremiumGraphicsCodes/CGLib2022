#include "PhysicsSolverExportCommand.h"

#include "../CrystalPhysics/MVP/IMVPFluidScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"
#include "Crystal/IO/PLYFileWriter.h"

namespace {
	PublicLabel CommandNameLabel = "PhysicsSolverExportCommand";
	PublicLabel FluidIdsLabel = "FluidIds";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel DoExportMicroLabel = "DoExportMicro";
	PublicLabel AsBinaryLabel = "AsBinary";
}

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string PhysicsSolverExportCommand::getName()
{
	return ::CommandNameLabel;
}

PhysicsSolverExportCommand::Args::Args() :
	fluidIds(::FluidIdsLabel, {}),
	filePath(::FilePathLabel, ""),
	doExportMicro(::DoExportMicroLabel, false),
	asBinary(::AsBinaryLabel, true)
{
	add(&fluidIds);
	add(&filePath);
	add(&doExportMicro);
	add(&asBinary);
}

PhysicsSolverExportCommand::Results::Results()
{
}

PhysicsSolverExportCommand::PhysicsSolverExportCommand() :
	ICommand(&args, &results)
{}

PhysicsSolverExportCommand::PhysicsSolverExportCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{
}

bool PhysicsSolverExportCommand::execute(World* world)
{
	PLYFile file;
	file.properties.push_back(PLYProperty("x", PLYType::FLOAT));
	file.properties.push_back(PLYProperty("y", PLYType::FLOAT));
	file.properties.push_back(PLYProperty("z", PLYType::FLOAT));
	file.properties.push_back(PLYProperty("temperature", PLYType::FLOAT));
	for (const auto id : args.fluidIds.getValue()) {
		auto fluid = world->getScenes()->findSceneById<IMVPFluidScene*>(id);
		if (fluid == nullptr) {
			return false;
		}
		const auto macroParticles = fluid->getParticles();
		if (args.doExportMicro.getValue()) {
			for (const auto mp : macroParticles) {
				const auto micros = mp->getMassParticles();
				for (const auto micro : micros) {
					const auto pp = micro->position;
					PLYPoint p;
					p.values.push_back(pp.x);
					p.values.push_back(pp.y);
					p.values.push_back(pp.z);
					p.values.push_back(micro->getTemperature());
					file.vertices.push_back(p);
				}
			}
		}
		else {
			for (const auto mp : macroParticles) {
				const auto pp = mp->getPositionf();
				PLYPoint p;
				p.values.push_back(pp.x);
				p.values.push_back(pp.y);
				p.values.push_back(pp.z);
				p.values.push_back(mp->getTemperature());

				file.vertices.push_back(p);
			}
		}
	}

	PLYFileWriter writer;
	if (args.asBinary.getValue()) {
		const auto isOk = writer.writeBinary(args.filePath.getValue(), file);
		return isOk;
	}
	else {
		const auto isOk = writer.writeASCII(args.filePath.getValue(), file);
		return isOk;
	}
}
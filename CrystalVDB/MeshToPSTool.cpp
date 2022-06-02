#include <iostream>
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/VDBSceneCreateCommand.h"
#include "CrystalVDB/VDBCommand/VDBSTLFileReadCommand.h"
#include "CrystalVDB/VDBCommand/VDBMeshToVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBVolumeToPSCommand.h"
#include "CrystalVDB/VDBCommand/VDBPCDFileWriteCommand.h"

using namespace Crystal::VDB;

struct CommandLineOptions
{
    std::string inputMeshFilePath = "cube.stl";
    std::string outputPsFilePath = "points.pcd";
    double divideLength = 0.1;

    void parse(const std::vector<std::string>& strs) {
        for (int i = 0; i < strs.size(); ++i) {
            std::string str = strs[i];
            if (str == "-i") {
                i++;
                this->inputMeshFilePath = strs[i];
            }
            else if (str == "-o") {
                i++;
                this->outputPsFilePath = strs[i];
            }
            else if (str == "-l") {
                i++;
                this->divideLength = std::stod(strs[i]);
            }
        }
    }
};

int main(int argc, char* argv[])
{
    CommandLineOptions options;
    std::vector<std::string> strs;
    for (int i = 0; i < argc; ++i) {
        strs.push_back(argv[i]);
    }
    options.parse(strs);

    Crystal::Scene::World world;

    std::cout << "Initializing VDB...";
    {
        VDBInitCommand command;
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    std::cout << "Creating VDB Mesh...";
    int meshId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBMesh");
        VDBSceneCreateCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
        meshId = std::any_cast<int>(command.getResults().newId.value);
    }

    std::cout << "Reading STL...";
    {
        VDBSTLFileReadCommand::Args args;
        args.filePath.setValue(options.inputMeshFilePath);
        args.vdbMeshId.setValue(meshId);
        VDBSTLFileReadCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    int volumeId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBVolume");
        VDBSceneCreateCommand command(args);
        command.execute(&world);
        volumeId = std::any_cast<int>(command.getResults().newId.value);
    }

    std::cout << "Converting Mesh to Volume...";
    {
        VDBMeshToVolumeCommand::Args args;
        args.divideLength.setValue(options.divideLength);
        args.vdbMeshId.setValue(meshId);
        args.vdbVolumeId.setValue(volumeId);
        VDBMeshToVolumeCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    std::cout << "Creating VDB Points...";
    int psId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBPoints");
        VDBSceneCreateCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }

        psId = std::any_cast<int>(command.getResults().newId.value);
    }

    std::cout << "Converting Volume to Points...";
    {
        VDBVolumeToPSCommand::Args args;
        args.vdbParticleSystemId.setValue( psId );
        args.vdbVolumeId.setValue( volumeId );
        VDBVolumeToPSCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    std::cout << "Writing PCD File...";
    {
        VDBPCDFileWriteCommand::Args args;
        args.vdbPsId.setValue(psId);
        args.filePath.setValue(options.outputPsFilePath);
        VDBPCDFileWriteCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }
}

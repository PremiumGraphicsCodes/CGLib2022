// VDBRunner.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include "CrystalVDB/VDBCommand/VDBCommandFactory.h"
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalScene/Command/JSONFileWriter.h"
#include "CrystalScene/Command/JSONFileReader.h"

using namespace Crystal::Command;
using namespace Crystal::VDB;

void testDump()
{
	JSONFileWriter writer;
}

int main(int argc, char** argv)
{
	Crystal::Scene::World world;

	if (argc < 1) {
		std::cout << "usage input.json" << std::endl;
		return -1;
	}

	const std::string inputFile = argv[1];//"./TestFiles/command.json"

	VDBInitCommand initCommand;
	initCommand.execute(&world);

	VDBCommandFactory factory;
	JSONFileReader reader;
	const auto isOk = reader.read(inputFile, factory);
	if (!isOk) {
		std::cout << "File read failed" << std::endl;
		return -1;
	}
	auto commands = reader.getCommands();
	for (auto& c : commands) {
		std::cout << "Start " << c->getCommandName() << std::endl;
		const auto isOk = c->execute(&world);
		if (!isOk) {
			std::cout << "Failed" << std::endl;
		}
		std::cout << "End " << c->getCommandName() << std::endl;
	}
}


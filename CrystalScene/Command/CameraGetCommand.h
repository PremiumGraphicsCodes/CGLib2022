#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraGetCommand : public ICommand
{
public:
	struct Results : IResults
	{
		Results();

		Result< double > near;
		Result< double > far;
		Result< Math::Vector3dd > eyePosition;
		Result< Math::Vector3dd > targetPosition;
		Result< Math::Vector3dd > upVector;
		Result< Math::Matrix4dd > projectionMatrix;
		Result< Math::Matrix4dd > rotationMatrix;
	};

	CameraGetCommand() :
		ICommand(nullptr, &results)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Results results;
};

	}
}
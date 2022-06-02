#pragma once

#include <memory>

#include "Crystal/Util/UnCopyable.h"
#include "CrystalScene/Command/ICommand.h"
#include "CrystalScene/Command/CommandFactory.h"

namespace Crystal {
	namespace VDB {

class VDBCommandFactory : public Command::ICommandFactory
{
public:
	std::unique_ptr<Command::ICommand> createCommand(const std::string& name) const override;
};
	}
}
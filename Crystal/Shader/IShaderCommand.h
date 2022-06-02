#pragma once

#include <vector>
#include <string>

namespace Crystal {
	namespace Shader {
		class ShaderObject;

		class IShaderCommand
		{
		public:
			virtual ~IShaderCommand() {}

			virtual void execute(ShaderObject* shader) = 0;
		};

		class SendVertexAttribute3dfCommand : public IShaderCommand
		{
		public:
			SendVertexAttribute3dfCommand()
			{}

			SendVertexAttribute3dfCommand(const std::vector<float>& positions) :
				positions(positions)
			{
			}

			void execute(ShaderObject* shader) override;

		private:
			std::vector<float> positions;
		};

		class EnableVertexAttributeCommand : public IShaderCommand
		{
		public:
			EnableVertexAttributeCommand()
			{}

			EnableVertexAttributeCommand(const std::string& name) :
				name(name)
			{}

			void execute(ShaderObject* shader) override;

		private:
			std::string name;
		};
	}
}
#pragma once

#include <string>

namespace Crystal {
	namespace Scene {

		namespace  SceneTypeLabels {
			constexpr auto None = "None";
			constexpr auto Root = "Root";
			constexpr auto ParticleSystemScene = "ParticleSystemScene";
			constexpr auto WireFrameScene = "WireFrameScene";
			constexpr auto PolygonMeshScene = "PolygonMeshScene";
			constexpr auto TriangleMeshScene = "TriangleMeshScene";
			constexpr auto CSGScene = "CSGScene";
			constexpr auto LightScene = "LightScene";
			constexpr auto MaterialScene = "MaterialScene";
			constexpr auto TextureScene = "TextureScene";
			constexpr auto ShaderScene = "ShaderScene";
			constexpr auto CameraScene = "CameraScene";
			constexpr auto TransformScene = "TransformScene";
		}

		class SceneType
		{
		public:
			SceneType(const char* const name) :
				name(name)
			{
			}

			/*
			SceneType(const std::string& name) :
				name(name)
			{
			}
			*/

			bool operator==(const SceneType& rhs) const {
				return this->name == rhs.name;
			}

				/*
			bool operator==(const std::string& rhs) const {
				return this->name == rhs;
			}
			*/

			std::string getName() const { return name; }

		private:
			const std::string name;
		};

static bool isShapeScene(const SceneType& type)
{
	if (type == SceneTypeLabels::ParticleSystemScene
		|| type == SceneTypeLabels::WireFrameScene
//		|| type == SceneType::TriangleMeshScene
		|| type == SceneTypeLabels::CSGScene) {
		return true;
	}
	return false;
}
	}
}
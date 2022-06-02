#pragma once

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace VDB {
		class VDBMeshScene;
		class VDBVolumeScene;

class VDBPolygonMeshConverter
{
public:
	void fromVDB(const VDBMeshScene& src, Shape::PolygonMesh* dest);

private:
};

	}
}
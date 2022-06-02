#include "MVPFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

MVPFluidScene::MVPFluidScene(const int id, const std::string& name) :
	IMVPFluidScene(id, name),
	isBoundary_(false)
{
}

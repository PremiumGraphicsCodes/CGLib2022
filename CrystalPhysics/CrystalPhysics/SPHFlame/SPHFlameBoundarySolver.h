#include "../../../Crystal/Math/Box3d.h"

#include <vector>

namespace Crystal {
	namespace Physics {
		class SPHFlameParticle;

class SPHFlameBoundarySolver
{
public:
	SPHFlameBoundarySolver() :
		timeStep(1.0f) {};

	SPHFlameBoundarySolver(const float timeStep, const Math::Box3dd& boundary);

	void solve(const std::vector<SPHFlameParticle*>& particles);

private:
	Math::Vector3df getBoundaryForce(const Math::Vector3df& center);

	Math::Vector3df getForceX(const float x);
	Math::Vector3df getForceY(const float y);
	Math::Vector3df getForceZ(const float z);

	float getForce(const float over);

	const float timeStep;
	const Math::Box3dd boundary;
};

	}
}
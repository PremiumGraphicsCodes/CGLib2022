#include "../../../Crystal/Math/Box3d.h"

#include <vector>

namespace Crystal {
	namespace Physics {
		class CSPHParticle;

class CSPHBoundarySolver
{
public:
	CSPHBoundarySolver() :
		timeStep(1.0f) {};

	CSPHBoundarySolver(const float timeStep, const Math::Box3dd& boundary);

	void solve(const std::vector<CSPHParticle*>& particles);

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
#include "WPCA.h"

#include "../../../Crystal/Shape/IParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Physics;

Matrix3df WPCA::calculateCovarianceMatrix(Shape::IParticle* center, const std::vector<Shape::IParticle*>& positions, const float radius)
{
	const auto weightedMean = calculateWeightedMean(center, positions, radius);

	Matrix3df matrix(0,0,0,0,0,0,0,0,0);
	for (const auto& pw : pws) {
		const auto p = pw.position;
		const auto w = pw.weight;

		const auto v = weightedMean - p;
		//const auto vt = glm::transpose(v);
		//Matrix3df m()
		const auto x00 = v[0] * v[0];
		const auto x01 = v[0] * v[1];
		const auto x02 = v[0] * v[2];
		const auto x10 = v[1] * v[0];
		const auto x11 = v[1] * v[1];
		const auto x12 = v[1] * v[2];
		const auto x20 = v[2] * v[0];
		const auto x21 = v[2] * v[1];
		const auto x22 = v[2] * v[2];

		const Matrix3df m
		(
			x00, x01, x02,
			x10, x11, x12,
			x20, x21, x22
		);

		matrix += w * m;
	}
	matrix /= totalWeight;

	return matrix;
}

Vector3df WPCA::calculateWeightedMean(Shape::IParticle* center, const std::vector<Shape::IParticle*>& positions, const float radius)
{
	Vector3df weightedCenter(0.0f, 0.0f, 0.0f);
	for (const auto pw : pws) {
		weightedCenter += pw.position * pw.weight;
	}
	weightedCenter /= totalWeight;

	return weightedCenter;
}

float WPCA::calculateWeight(const Vector3df& lhs, const Vector3df& rhs, const float radius)
{
	const auto distance = Crystal::Math::getDistance(lhs, rhs);
	if (distance > radius) {
		return 0.0f;
	}
	return 1.0f - std::pow((distance / radius), 3.0f);
}

void WPCA::setup(IParticle* center, const std::vector<IParticle*>& positions, const float radius)
{
	//std::vector<PositionWeight> pws;
	//pws.reserve(positions.size());
	for (const auto& p : positions) {
		const auto w = calculateWeight(center->getPosition(), p->getPosition(), radius);
		PositionWeight pw;
		pw.position = p->getPosition();
		pw.weight = w;
		this->pws.push_back(pw);
	}

	this->totalWeight = 0.0f;
	for (const auto& pw : pws) {
		this->totalWeight += pw.weight;
	}

}
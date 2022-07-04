#pragma once

#include <vector>
#include <memory>

#include "SPHAnisotoropicParticle.h"

#include "Crystal/Shape/Volume.h"
#include "../../../CrystalSpace/CrystalSpace/SparseVolume.h"

namespace Crystal {
	namespace Physics {


class SPHVolumeConverter
{
public:
	//void add(Shape::IParticle* particle);

	std::unique_ptr<Space::SparseVolumef> buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength);

	std::unique_ptr<Space::SparseVolumef> buildAnisotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength);

	const std::vector<std::unique_ptr<SPHAnisotoropicParticle>>& getParticles() const { return particles; }

	//std::vector < Shape::Volume<double>* > getVolumes() { return volumes; }

private:
	std::unique_ptr<Space::SparseVolumef> createSparseVolume(const std::vector<Math::Vector3dd>& particles, const float cellLength);

	void calculateDensity(const float searchRadius);

	void calculateAnisotropy(const float searchRadius);
	
	//std::vector<Shape::IParticle*> particles;

	//std::vector<Shape::Volume<double>*> volumes;
	std::vector<std::unique_ptr<SPHAnisotoropicParticle>> particles;
};
	}
}
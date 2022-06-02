#pragma once

#include <cmath>
#include "Tolerance.h"

namespace Crystal {
	namespace Math {

class Gaussian3d
{
public:
	Gaussian3d() :
		//mu(0.0),
		tau(1.0)
	{}

	Gaussian3d(/*const double mu,*/ const double tau) :
		//mu(mu),
		tau(tau)
	{}

	double getValue(const double x, const double y, const double z) const
	{
		const auto scale = 1.0 / ( std::pow( std::sqrt(2.0 * PI), 3.0) * std::pow(tau,3.0));
		const auto power = -(x * x + y * y + z * z) / (2.0 * tau * tau);
		return scale * std::exp(power);
	}

	double getValue(const double r) const
	{
		const auto scale = 1.0 / (std::pow(std::sqrt(2.0 * PI), 3.0) * std::pow(tau, 3.0));
		const auto power = -(r * r) / (2.0 * tau * tau);
		return scale * std::exp(power);
	}

private:
//			const double mu;
	const double tau;
};
	}
}
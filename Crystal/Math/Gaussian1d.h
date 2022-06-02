#pragma once

#include <cmath>
#include "Tolerance.h"

namespace Crystal {
	namespace Math {

class Gaussian1d
{
public:
	Gaussian1d() :
		mu(0.0),
		tau(1.0)
	{}

	Gaussian1d(const double mu, const double tau) :
		mu(mu),
		tau(tau)
	{}

	double getValue(const double x) const
	{
		const auto scale = 1.0 / ( std::sqrt(2.0 * PI) * tau );
		const auto power = -(x - mu) * (x - mu) / (2.0 * tau * tau);
		return scale * std::exp(power);
	}

private:
	const double mu;
	const double tau;
};
	}
}
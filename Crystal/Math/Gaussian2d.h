#pragma once

#include <cmath>
#include "Tolerance.h"

namespace Crystal {
	namespace Math {

		class Gaussian2d
		{
		public:
			Gaussian2d() :
				//mu(0.0),
				tau(1.0)
			{}

			Gaussian2d(/*const double mu,*/ const double tau) :
				//mu(mu),
				tau(tau)
			{}

			double getValue(const double x, const double y) const
			{
				const auto scale = 1.0 / (2.0 * PI) * std::pow(tau, 2);
				const auto power = -(x * x + y * y) / (2.0 * tau * tau);
				return scale * std::exp(power);
			}

		private:
			//			const double mu;
			const double tau;
		};
	}
}
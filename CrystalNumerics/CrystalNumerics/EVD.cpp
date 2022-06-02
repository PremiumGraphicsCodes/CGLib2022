#include "EVD.h"

#include <Eigen/Core>
#include <Eigen/Dense>

#include "Converter.h"

using namespace Eigen;

using namespace Crystal::Math;
using namespace Crystal::Numerics;

EVD::EVD3dResult EVD::calculate(const Math::Matrix3dd& lhs)
{
	const auto m = Impl::Converter::toEigen(lhs);

	EigenSolver<Eigen::Matrix3d> es(m);

	//VectorXcd v = es.eigenvectors().col(0);
	//cout << "If v is the corresponding eigenvector, then lambda * v = " << endl << lambda * v << endl;
	//cout << "... and A * v = " << endl << A.cast<complex<double> >() * v << endl << endl;

	Vector3cd D = es.eigenvalues();
	Matrix3cd V = es.eigenvectors();
	//cout << "Finally, V * D * V^(-1) = " << endl << V * D * V.inverse() << endl;

	EVD3dResult result;
	result.isOk = true;
	//result.eigenValues = Vector3dd(D[0].real(), D[1].real(), D[2].real());// Impl::Converter::fromEigen(D);
	//result.eigenVectors = Impl::Converter::fromEigen(V);
	return result;
}

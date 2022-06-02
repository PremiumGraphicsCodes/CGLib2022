#include "pch.h"
#include "../CrystalPhysics/MPS/MPSParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	std::vector<MPSParticle*> createTestParticles2d()
	{
		std::vector<MPSParticle*> particles;
		const auto length = 0.1;
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < 7; ++j) {
				const auto x = i * length;
				const auto y = j * length;
				const auto pos = Vector3df(x, y, 0.0f);
				auto p = new MPSParticle(pos);
				particles.emplace_back(p);
			}
		}
		for (auto p : particles) {
			if (p != particles[24]) {
				particles[24]->addNeighbor(p);
			}
		}
		//particles[24]->addNeighbor(particles);
		return particles;
	}

	std::vector<MPSParticle*> createTestParticlesForPressure()
	{
		std::vector<MPSParticle*> particles;
		const auto length = 1.0;
		for (int i = 0; i < 5; ++i) {
			const float pressure = i * 10.0;
			for (int j = 0; j < 5; ++j) {
				const auto x = j * length;
				const auto y = i * length;
				const auto pos = Vector3df(x, y, 0.0f);
				auto p = new MPSParticle(pos);
				p->setPressure(pressure);
				particles.emplace_back(p);
			}
		}
		for (auto p : particles) {
			if (p != particles[12]) {
				particles[12]->addNeighbor(p);
			}
		}
		//particles[24]->addNeighbor(particles);
		return particles;
	}

	/*
	std::vector<MPSParticle*> createTestParticlesForViscosity()
	{
		std::vector<MPSParticle*> particles;
		const auto length = 1.0;
		for (int i = 0; i < 5; ++i) {
			const float pressure = i * 10.0;
			for (int j = 0; j < 5; ++j) {
				const auto x = j * length;
				const auto y = i * length;
				const auto pos = Vector3df(x, y, 0.0f);
				auto p = new MPSParticle(pos);
				p->setPressure(pressure);
				particles.emplace_back(p);
			}
		}
		for (auto p : particles) {
			if (p != particles[12]) {
				particles[12]->addNeighbor(p);
			}
		}
		//particles[24]->addNeighbor(particles);
		return particles;
	}
	*/
}

TEST(MPSParticleTest, TestCalculateNumberDensity)
{
	const auto ps = ::createTestParticles2d();
	// This expected data is from the book "粒子法入門"(in Japanese).
	ps[24]->calculateNumberDensity(0.21);
	const auto actual = ps[24]->getNumberDensity();
	const float expected = 6.539696;
	EXPECT_NEAR(expected, actual, 1.0e-5);

	for (auto p : ps) {
		delete p;
	}
}

TEST(MPSParticleTest, TestCalculatePressureGradient)
{
	const auto ps = ::createTestParticlesForPressure();
	// This expected data is from the book "粒子法入門"(in Japanese).
	ps[12]->calculateNumberDensity(1.5f);
	const auto n0 = ps[12]->getNumberDensity();
	ps[12]->setN0(n0);
	ps[12]->calculatePressureGradient(1.5f);
	const auto force = ps[12]->getForce();
	Vector3df expected(0.0, 10.0f, 0.0f);
	EXPECT_TRUE(::areSame(expected, force, 1.0e-5f));
	for (auto p : ps) {
		delete p;
	}
}

TEST(MPSParticleTest, TestCalculateViscosity)
{
	const auto ps = ::createTestParticlesForPressure();
	// This expected data is from the book "粒子法入門"(in Japanese).
	const auto p = ps[12];
	p->calculateN0(1.5f);
	p->calculateLamda0(1.5f);
	p->calculateViscosity(1.5f);
}
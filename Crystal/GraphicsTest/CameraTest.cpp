#include "gtest/gtest.h"
#include "../Graphics/Camera.h"

#include "../Math/Matrix4d.h"
#include "../ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

#include "../Math/Tolerance.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

/*
TEST(CameraTest, TestGetModelViewMatrix)
{
	ICamera c;
	c.lookAt(glm::vec3(0,0,10), glm::vec3(0, 0, 0), glm::vec3(0,1,0));
	const auto& actual = c.getModelViewMatrix();
	glm::mat4x4 expected(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,10.0f, 1.0f
	);
	//EXPECT_TRUE( areSame(expected, actual);
}
*/

TEST(CameraTest, TestGetForward)
{
	Camera c;
	c.lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	const auto& actual = c.getForward();
	const Vector3df expected(0, 0, 1);
	EXPECT_EQ(expected, actual);
}

TEST(CameraTest, TestGetUp)
{
	Camera c;
	c.lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	const auto& actual = c.getUp();
	const Vector3df expected(0, 1, 0);
	EXPECT_EQ(expected, actual);
}

TEST(CameraTest, TestGetRight)
{
	Camera c;
	c.lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	const auto& actual = c.getRight();
	const Vector3df expected(1, 0, 0);
	EXPECT_EQ(expected, actual);
}

TEST(CameraTest, TestRotate)
{
	Camera c;
	c.lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	c.rotate( Matrix3df(rotationMatrixY(Crystal::Math::PI)));
	{
		const auto& actual = c.getEye();
		const Vector3df expected(0, 0, 10);
		EXPECT_TRUE( areSame( expected, actual, 1.0e-9f));
	}
	{
		const auto& actual = c.getUp();
		const Vector3df expected(0, 1, 0);
		EXPECT_TRUE(areSame(expected, actual, 1.0e-9f));
	}
	{
		const auto& actual = c.getRight();
		const Vector3df expected(-1, 0, 0);
		EXPECT_TRUE(areSame(expected, actual, 1.0e-9f));
	}
}

/*
TEST(CameraTest, TestGetProjectionMatrix)
{
	ICamera c;
	c.setNear(0.0f);
	c.setFar(10.0f);
	c.setOrtho();
	const auto& actual = c.getProjectionMatrix();
	const glm::mat4x4 expected(
		2.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -0.2, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);
	EXPECT_EQ(expected, actual);
}
*/
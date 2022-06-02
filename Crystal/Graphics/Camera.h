#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"


namespace Crystal {
	namespace Graphics {

class Camera
{
public:
	Camera();

	Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, const float near_, const float far_);

	void setOrtho() { this->isOrtho = true; }

	void setPerspective() { this->isOrtho = false; }

	void moveEye(const glm::vec3& v);

	void setEye(const glm::vec3& p);

	void setTarget(const Math::Vector3df& target);

	Math::Vector3df getTarget() const { return target; }

	void lookAt(const Math::Vector3df& eye, const Math::Vector3df& target, const Math::Vector3df& up);

	Math::Vector3df getEye() const { return eye; }

	Math::Matrix4df getModelViewMatrix() const;

	void setFar(const float f) { this->far_ = f; }

	void setNear(const float n) { this->near_ = n; }

	float getFar() const { return far_; }

	float getNear() const { return near_; }

	Math::Matrix4df getProjectionMatrix() const;

	void zoom(const float s) { this->scale *= (1.0f + s); }

	Math::Vector3df getRight() const;

	Math::Vector3df getUp() const;

	Math::Vector3df getForward() const;

	Math::Matrix4df getRotationMatrix() const;

	void rotate(const Math::Matrix3df& matrix);


private:
	Math::Vector3df eye;
	Math::Vector3df target;
	Math::Vector3df up;
	float near_;
	float far_;
	float scale;
	bool isOrtho;
};

	}
}
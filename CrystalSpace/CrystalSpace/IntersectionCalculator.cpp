#include "IntersectionCalculator.h"

#include "../../Crystal/Math/Line3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Math/Plane3d.h"
#include "../../Crystal/Math/Quad3d.h"
#include "../../Crystal/Math/Box3d.h"

#include "../../Crystal/Shape/PolygonMesh.h"

//#define GLM_ENABLE_EXPERIMENTAL
//#include "../../Crystal/ThirdParty/glm-0.9.9.3/glm/gtx/intersect.hpp"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

bool IntersectionCalculator::calculateIntersection(const Ray3d& ray, const Sphere3dd& sphere, const double tolerance)
{
	const auto& direction = ray.getDirection();
	const auto& diff = sphere.getCenter() - ray.getOrigin();
	const auto t0 = glm::dot(diff, direction);
	const auto distanceSquared = glm::dot(diff, diff) - t0 * t0;
	const auto sphereRadiusSquared = sphere.getRadius() * sphere.getRadius();
	if (distanceSquared > sphereRadiusSquared)
	{
		return false;
	}
	const auto t1 = std::sqrt(sphereRadiusSquared - distanceSquared);
	const auto intersectionDistance = t0 > t1 + tolerance ? t0 - t1 : t0 + t1;
	if (intersectionDistance > tolerance) {
		const auto& i = ray.getPosition(intersectionDistance);
		const auto& normal = glm::normalize( i - sphere.getCenter() );
		intersections.push_back(Intersection(i, normal));
		return true;
	}
	return false;
}

bool IntersectionCalculator::calculateIntersection(const Line3dd& line, const Sphere3dd& sphere, const double tolerance)
{
	const auto& dir = glm::normalize(line.getDirection());
	const auto diff = sphere.getCenter() - line.getStart();
	const auto t0 = glm::dot(diff, dir);
	const auto dSquared = dot(diff, diff) - t0 * t0;
	const auto sphereRadiusSquared = sphere.getRadius() * sphere.getRadius();
	if (dSquared > sphereRadiusSquared)
	{
		return false;
	}
	auto t1 = sqrt(sphereRadiusSquared - dSquared);
	if (t0 < t1 + tolerance) {
		t1 = -t1;
	}
	Intersection i1;
	i1.position = line.getStart() + dir * (t0 - t1);
	i1.normal = glm::normalize(i1.position - sphere.getCenter());
	intersections.push_back(i1);
	Intersection i2;
	i2.position = line.getStart() + dir * (t0 + t1);
	i2.normal = glm::normalize(i2.position - sphere.getCenter());
	intersections.push_back(i2);
	return true;
}

bool IntersectionCalculator::calculateIntersection(const Line3dd& line, const Triangle3d& triangle, const double tolerance)
{
	const auto& plane = triangle.toPlane();

	IntersectionCalculator innerAlgo;
	if (!innerAlgo.calculateIntersection(line, plane, tolerance)) {
		return false;
	}

	auto s = innerAlgo.getIntersections()[0].position;
	if (triangle.isInside(s)) {
		Intersection intersection;
		intersection.position = s;
		intersection.normal = triangle.getNormal();
		intersections.push_back(intersection);
		return true;
	}
	return false;
}

bool IntersectionCalculator::calculateIntersection(const Line3dd& line, const Quad3d& quad, const double tolerance)
{
	const auto& plane = quad.toPlane();

	IntersectionCalculator innerAlgo;
	if (!innerAlgo.calculateIntersection(line, plane, tolerance)) {
		return false;
	}

	auto s = innerAlgo.getIntersections()[0].position;
	if (quad.isInside(s)) {
		Intersection intersection;
		intersection.position = s;
		intersection.normal = quad.getNormal();
		intersections.push_back(intersection);
		return true;
	}
	return false;
}

bool IntersectionCalculator::calculateIntersection(const Ray3d& ray, const Quad3d& quad, const double tolerance)
{
	const auto& plane = quad.toPlane();

	IntersectionCalculator innerAlgo;
	if (!innerAlgo.calculateIntersection(ray, plane, tolerance)) {
		return false;
	}

	auto s = innerAlgo.getIntersections()[0].position;
	if (quad.isInside(s)) {
		Intersection intersection;
		intersection.position = s;
		intersection.normal = quad.getNormal();
		intersections.push_back(intersection);
		return true;
	}
	return false;
}

bool IntersectionCalculator::calculateIntersection(const Ray3d& ray, const Plane3d& plane, const double tolerance)
{
	const auto distance = plane.getDistance(ray.getOrigin());

	if (distance > -tolerance)
	{
		const Intersection intersection(ray.getPosition(distance), plane.getNormal());
		intersections.push_back(intersection);
		return true;
	}
	return false;
}

bool IntersectionCalculator::calculateIntersection(const Ray3d& ray, const Triangle3d& triangle, const double tolerance)
{
	auto res = calculateIntersectionParameters(ray, triangle, tolerance);
	if (res.has_value()) {
		Intersection i;
		i.position = ray.getPosition(res.value().x);
		this->intersections.push_back(i);
		return true;
	}
	return false;
}

// reference https://pheema.hatenablog.jp/entry/ray-triangle-intersection
std::optional<Vector3dd> IntersectionCalculator::calculateIntersectionParameters(const Math::Ray3d& ray, const Math::Triangle3d& triangle, const double tolerance)
{
	const auto v0 = triangle.getVertices()[0];
	const auto v1 = triangle.getVertices()[1];
	const auto v2 = triangle.getVertices()[2];

	const auto e1 = v1 - v0;
	const auto e2 = v2 - v0;

	const auto o = ray.getOrigin();
	const auto d = ray.getDirection();
	const auto alpha = glm::cross(d, e2);
	const auto det = glm::dot(e1, alpha);

	// 三角形に対して、レイが平行に入射するような場合 det = 0 となる。
	// det が小さすぎると 1/det が大きくなりすぎて数値的に不安定になるので
	// det ≈ 0 の場合は交差しないこととする。
	if (-tolerance < det && det < tolerance) {
		return std::nullopt;
	}

	const auto invDet = 1.0 / det;
	const auto r = o - v0;

	// u が 0 <= u <= 1 を満たしているかを調べる。
	const auto u = glm::dot(alpha, r) * invDet;
	if (u < 0.0 || u > 1.0) {
		return std::nullopt;
	}

	const auto beta = glm::cross(r, e1);

	// v が 0 <= v <= 1 かつ u + v <= 1 を満たすことを調べる。
	// すなわち、v が 0 <= v <= 1 - u をみたしているかを調べればOK。
	const auto v = glm::dot(d, beta) * invDet;
	if (v < 0.0f || u + v > 1.0f) {
		return std::nullopt;
	}

	// t が 0 <= t を満たすことを調べる。
	const auto t = glm::dot(e2, beta) * invDet;
	if (t < 0.0f) {
		return std::nullopt;
	}

	return Vector3dd(t, u, v);
}


// ref https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
bool IntersectionCalculator::calculateIntersection(const Ray3d& ray, const Box3dd& box, const double tolerance)
{
	// tmin, tmax -> parameter

	const auto origin = ray.getOrigin();
	const auto dir = ray.getDirection();

	const auto min = box.getMin();
	const auto max = box.getMax();
	auto tmin = (min.x - origin.x) / dir.x;
	auto tmax = (max.x - origin.x) / dir.x;

	if (tmin > tmax) std::swap(tmin, tmax);

	auto tymin = (min.y - origin.y) / dir.y;
	auto tymax = (max.y - origin.y) / dir.y;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	auto tzmin = (min.z - origin.z) / dir.z;
	auto tzmax = (max.z - origin.z) / dir.z;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	intersections.push_back( Intersection( ray.getPosition(tmin), Vector3dd() ));
	intersections.push_back(Intersection(ray.getPosition(tmax), Vector3dd()));

	return true;
}

bool IntersectionCalculator::calculateIntersection(const Line3dd& line, const Plane3d& plane, const double tolerance)
{
	// 線分の始点が三角系の裏側にあれば、当たらない
	const auto planeToStart = plane.getDistance(line.getStart());	// 線分の始点と平面の距離
	if (planeToStart <= tolerance) {
		return false;
	}

	// 線分の終点が三角系の表側にあれば、当たらない
	const auto planeToEnd = plane.getDistance(line.getEnd());	// 線分の終点と平面の距離
	if (planeToEnd >= -tolerance) {
		return false;
	}

	// 直線と平面との交点を取る
	const auto denom = planeToStart - planeToEnd;
	const auto param = planeToStart / denom;

	Intersection i(line.getPosition(param), plane.getNormal());
	intersections.push_back(i);
	return true;
}

bool IntersectionCalculator::calculateIntersection(const Triangle3d& lhs, const Triangle3d& rhs, const double tolerance)
{
	const auto& vertices = lhs.getVertices();
	const auto l1 = Line3dd::fromPoints(vertices[0], vertices[1]);
	const auto l2 = Line3dd::fromPoints(vertices[1], vertices[2]);
	const auto l3 = Line3dd::fromPoints(vertices[2], vertices[0]);
	const auto found1 = calculateIntersection(l1, rhs, tolerance);
	const auto found2 = calculateIntersection(l2, rhs, tolerance);
	const auto found3 = calculateIntersection(l3, rhs, tolerance);
	return (found1 || found2 || found3);
}
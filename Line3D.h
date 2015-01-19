#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

// glm
#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Line3D {
public:
	Line3D(const glm::vec3 &p0, const glm::vec3 &p1);
	Line3D(const Line3D &line3d);
	Line3D& operator=(const Line3D &line3d);

	void copy(const Line3D &src, Line3D &dst);

	glm::vec3 src() const;
	glm::vec3 dir() const;

	bool is_valid() const;

	// point - line
	glm::vec3 closest_point(const glm::vec3 &p) const;
	float distance(const glm::vec3 &p) const;

	// line - line
	bool is_parallel(const Line3D &l) const;
	glm::vec3 closest_point(const Line3D &l1) const;
	float closest_distance(const Line3D &line) const;
	glm::vec3 closest_midpoint(const Line3D &line) const;

	std::string to_s() const;

protected:
	glm::vec3 src_;
	glm::vec3 dir_;
};

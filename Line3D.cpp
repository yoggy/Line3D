#include "Line3D.h"

#include <sstream>

Line3D::Line3D(const glm::vec3 &p0, const glm::vec3 &p1)
{
	this->src_ = p0;
	this->dir_ = glm::normalize(p1 - p0);
}

Line3D::Line3D(const Line3D &line3d)
{
	copy(line3d, *this);
}

Line3D& Line3D::operator=(const Line3D &line3d)
{
	copy(line3d, *this);
	return *this;
}

void Line3D::copy(const Line3D &src, Line3D &dst)
{
	dst.src_ = src.src_;
	dst.dir_ = src.dir_;
}

glm::vec3 Line3D::src() const
{
	return src_;
}

glm::vec3 Line3D::dir() const
{
	return dir_;
}

bool Line3D::is_valid() const
{
	if (glm::distance(glm::vec3(0, 0, 0), dir_) < 1.0e-5) {
		return false;
	}
	return true;
}

glm::vec3 Line3D::closest_point(const glm::vec3 &p) const
{
	if (is_valid() == false) {
		return src_;
	}

	glm::vec3 sp = p - src_;
	float st_len = glm::dot(dir_, sp);

	glm::vec3 cp = dir_ * st_len;

	return cp;
}

float Line3D::distance(const glm::vec3 &p) const
{
	if (is_valid() == false) {
		glm::vec3 sp = p - src_;
		return glm::distance(glm::vec3(0, 0, 0), sp);
	}

	glm::vec3 cp = closest_point(p);
	glm::vec3 cp_p = p - cp;

	float d = glm::distance(glm::vec3(0, 0, 0), cp_p);

	return d;
}

bool Line3D::is_parallel(const Line3D &l) const
{
	float dot = abs(glm::dot(this->dir_, l.dir_));
	float diff = abs(1.0f - dot);

	if (diff < 1.0e-7) {
		return true;
	}

	return false;
}

glm::vec3 Line3D::closest_point(const Line3D &l1) const
{
	using namespace glm;

	const Line3D &l0 = *this;

	// parallel check 
	if (l0.is_parallel(l1)) {
		return glm::vec3(0, 0, 0);
	}

	glm::vec3 ss = l1.src_ - l0.src_;
	float dot_nn = dot(l0.dir_, l1.dir_);

	float t = (dot(l0.dir_, ss) - dot_nn * dot(l1.dir_, ss)) / (1 - dot_nn * dot_nn);

	glm::vec3 p = l0.src_ + t * l0.dir_;

	return p;
}

float Line3D::closest_distance(const Line3D &line) const
{
	glm::vec3 p0 = this->closest_point(line);
	glm::vec3 p1 = line.closest_point(*this);

	return glm::distance(p0, p1);
}

glm::vec3 Line3D::closest_midpoint(const Line3D &line) const
{
	glm::vec3 p0 = this->closest_point(line);
	glm::vec3 p1 = line.closest_point(*this);

	glm::vec3 m = p0 + (p1 - p0) * 0.5f;

	return m;
}

std::string Line3D::to_s() const
{
	std::stringstream ss;
	ss << "Line3D{";
	ss << "src_:[" << src_.x << ", " << src_.y << ", " << src_.z << "], ";
	ss << "dir_:[" << dir_.x << ", " << dir_.y << ", " << dir_.z << "]}";
	return ss.str();
}

#include <iostream>
#include "Line3D.h"

int main(int argc, char* argv[])
{
	Line3D line001(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	Line3D line010(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1));

	std::cout << "line001 = " << line001.to_s() << std::endl;
	std::cout << "line010 = " << line010.to_s() << std::endl;

	std::cout << "line001.distance(glm::vec3(0, 1, 0)) = " << line001.distance(glm::vec3(0, 1, 0)) << std::endl;
	std::cout << "line010.distance(glm::vec3(0, 1, 0)) = " << line010.distance(glm::vec3(0, 1, 0)) << std::endl;

	std::cout << "line001.closest_point(line010) = " << glm::to_string(line001.closest_point(line010)) << std::endl;
	std::cout << "line010.closest_point(line001) = " << glm::to_string(line010.closest_point(line001)) << std::endl;

	std::cout << "line001.closest_distance(line010) = " << line001.closest_distance(line010) << std::endl;

	std::cout << "line001.closest_midpoint(line010) = " << glm::to_string(line001.closest_midpoint(line010)) << std::endl;

	return 0;
}


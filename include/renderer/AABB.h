#ifndef _AABB_H
#define _AABB_H

#include <glm/glm.hpp>

class AABB {

	glm::vec3 min;
	glm::vec3 max;

public:

	AABB(glm::vec3 &min, glm::vec3 &max);

	const glm::vec3 &GetMin() const;

	const glm::vec3 &GetMax() const;

};

#endif
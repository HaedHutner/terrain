#include <renderer/AABB.h>

AABB::AABB(glm::vec3& min, glm::vec3& max)
	: min(min), max(max)
{
}

const glm::vec3& AABB::GetMin() const
{
	return min;
}

const glm::vec3& AABB::GetMax() const
{
	return max;
}

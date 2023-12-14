#include "utils/DDA.hpp"

using namespace Utils;

void DDA::ray(glm::vec3 startPoint, glm::vec3 direction)
{
  direction = glm::normalize(direction);

  glm::ivec3 step = glm::sign(direction);
  glm::vec3 stepWeight;
  stepWeight.x = sqrt(1 + pow(direction.y / direction.x, 2) + pow(direction.z / direction.x, 2));
  stepWeight.y = sqrt(1 + pow(direction.y / direction.y, 2) + pow(direction.z / direction.y, 2));
  stepWeight.z = sqrt(1 + pow(direction.y / direction.z, 2) + pow(direction.x / direction.z, 2));

  glm::ivec3 mapCheck = glm::floor(startPoint);
  glm::vec3 rayLength;
  rayLength.x = step.x * (float(mapCheck.x) + ((1.0f + step.x) / 2.0f) - startPoint.x) * stepWeight.x;
  rayLength.y = step.y * (float(mapCheck.y) + ((1.0f + step.y) / 2.0f) - startPoint.y) * stepWeight.y;
  rayLength.z = step.z * (float(mapCheck.z) + ((1.0f + step.z) / 2.0f) - startPoint.z) * stepWeight.z;
  
  std::vector<glm::vec3> collisionHistory;
  float distance = 0;
  while(distance < maxDistance)
  {
    if (rayLength.x < rayLength.y)
    {
      if (rayLength.x < rayLength.z)
      {
        mapCheck.x += step.x;
        distance = rayLength.x;
        rayLength.x += stepWeight.x; 
      }
      else
      {
        mapCheck.z += step.z;
        distance = rayLength.z;
        rayLength.z += stepWeight.z; 
      }
    }
    else
    {
      if (rayLength.y < rayLength.z)
      {
        mapCheck.y += step.y;
        distance = rayLength.y;
        rayLength.y += stepWeight.y; 
      } 
      else
      {
        mapCheck.z += step.z;
        distance = rayLength.z;
        rayLength.z += stepWeight.z; 
      }
    }

    glm::vec3 intersection = startPoint + direction * distance;
    collisionHistory.emplace_back(intersection);

    if (!onCollisionCallback(world, intersection, collisionHistory.data(), collisionHistory.size())) break;
  }
}

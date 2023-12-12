#ifndef DDA_HPP
#define DDA_HPP

#include <glm/glm.hpp>
#include <vector>

// forward declaration
class World;

namespace Utils
{
  class DDA
  {
    public:
      float maxDistance;
      World *world;
      bool (*onCollisionCallback)(World *world, glm::vec3 intersection, glm::vec3 *intersectionHistory, unsigned int intersectionCount);

      void ray(glm::vec3 startPoint, glm::vec3 direction);
  };
}

#endif


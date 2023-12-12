#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <glm/glm.hpp>
#include <stdexcept>

namespace Utils {
  class Quaternion
  {
    public:
      float x, y, z, w;

      Quaternion(float x = 0, float y = 0, float z = 0, float w = 0);
      Quaternion(float s, glm::vec3 v);
      Quaternion(Quaternion const &quaternion);

      void operator+=(Quaternion const &other);
      Quaternion operator+(Quaternion const &other) const;
      void operator-=(Quaternion const &other);
      Quaternion operator-(Quaternion const &other) const;

      void operator*=(Quaternion const &other);
      Quaternion operator*(Quaternion const &other) const;
      void operator*=(float k);
      Quaternion operator*(float k) const;

      float length() const;
      void convertToUnitNormQuaternion();
      static Quaternion normalize(Quaternion const &quaternion);
      static Quaternion conjugate(Quaternion const &quaternion);
      static Quaternion inverse(Quaternion const &quaternion);
      void normalize();
      void conjugate();
      void inverse();
      float getReal() const;
      glm::vec3 getIm() const;

      static glm::vec3 rotateVector(glm::vec3 target, float angle, glm::vec3 axis);
      static glm::vec3 rotateVector(glm::vec3 target, Quaternion q);
      static Quaternion rotate(Quaternion const &quaternion, float angle, glm::vec3 axis);
      void rotate(float angle, glm::vec3 axis);
  };
}

#endif


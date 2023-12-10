#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <glm/glm.hpp>
#include <iostream>

class Quaternion
{
public:
  float s;
  glm::vec3 v;
  Quaternion() {  }
  Quaternion (float s, glm::vec3 v) : s(s), v(v)
  {

  }

  void operator+=(Quaternion const& other)
  {
    s += other.s;
    v += other.v;
  }
  Quaternion operator+(Quaternion const& other) const
  {
    return Quaternion(s + other.s, v + other.v);
  }

  void operator-=(Quaternion const& other)
  {
    s -= other.s;
    v -= other.v;
  }
  Quaternion operator-(Quaternion const& other) const
  {
    return Quaternion(s - other.s, v - other.v);
  }

  void operator*=(Quaternion const& other)
  {
    throw std::runtime_error("Quaternion operation '*=' not implemented yet.");
  }
  Quaternion operator*(Quaternion const& other) const
  {
    float scalar = s * other.s - glm::dot(v, other.v);
    glm::vec3 imaginary = other.v * s + v * other.s + glm::cross(v, other.v);
    return Quaternion(scalar, imaginary);
  }

  void operator+=(float const& k)
  {
    s *= k;
    v *= k;
  }
  Quaternion operator*(float const& k) const
  {
    return Quaternion(k * s, k * v);
  }

  float length() const
  {
    return sqrt(s*s + v.x * v.x + v.y * v.y + v.z * v.z);
  }

  void normalize()
  {
    float l = length();
    if (l != 0)
    {
      s *= (1.0f / l);
      v *= (1.0f / l);
    }
  }

  void convertToUnitNormQuaternion()
  {
    float angle = glm::radians(s);
    glm::normalize(v);
    s = cos(angle * 0.5f);
    v *= sin(angle * 0.5f);
  }

  Quaternion conjugate() const
  {
    return Quaternion(s, v * (-1.0f));
  }

  Quaternion inverse() const
  {
    float l = length();
    l *= l;
    l = 1.0f / l;

    return conjugate() * l;
  }

  static glm::vec3 rotate(glm::vec3 target, float angle, glm::vec3 axis)
  {
    Quaternion p(0, target);

    axis = glm::normalize(axis);
    Quaternion q(angle, axis);
    q.convertToUnitNormQuaternion();
    Quaternion qInv = q.inverse(); 

    return (q * p * qInv).v;
  }

  static glm::vec3 rotate(glm::vec3 target, Quaternion q)
  {
    Quaternion p(0, target);
    return (q * p * q.inverse()).v;
  }

};

#endif


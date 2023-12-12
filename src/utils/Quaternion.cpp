#include "utils/Quaternion.hpp"

using namespace Utils;

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {  }
Quaternion::Quaternion(float s, glm::vec3 v) : Quaternion(s, v.x, v.y, v.z) {  }
Quaternion::Quaternion(Quaternion const &quaternion)
{
  x = quaternion.x;
  y = quaternion.y;
  z = quaternion.z;
  w = quaternion.w;
}

glm::vec3 Quaternion::rotateVector(glm::vec3 target, float angle, glm::vec3 axis)
{
  Quaternion p(0, target);
  return rotate(p, angle, axis).getIm();
}

glm::vec3 Quaternion::rotateVector(glm::vec3 target, Quaternion q)
{
  Quaternion p(0, target);
  return (q * p * inverse(q)).getIm();
}

Quaternion Quaternion::rotate(Quaternion const &quaternion, float angle, glm::vec3 axis)
{
  axis = glm::normalize(axis);
  Quaternion q(angle, axis);
  q.convertToUnitNormQuaternion();

  return q * quaternion * inverse(q);
}

void Quaternion::rotate(float angle, glm::vec3 axis)
{
  *this = rotate(*this, angle, axis);
}

void Quaternion::operator+=(Quaternion const &other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
}

Quaternion Quaternion::operator+(Quaternion const &other) const
{
  return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);  
}

void Quaternion::operator-=(Quaternion const &other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
}

Quaternion Quaternion::operator-(Quaternion const &other) const
{
  return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);  
}

void Quaternion::operator*=(Quaternion const &other)
{
  throw std::runtime_error("Quaternion operation '*=' not implemented yet.");
}

Quaternion Quaternion::operator*(Quaternion const &other) const
{
  float scalar = x * other.x - glm::dot(getIm(), other.getIm());
  glm::vec3 imaginary = other.getIm() * x + getIm() * other.x + glm::cross(getIm(), other.getIm());
  return Quaternion(scalar, imaginary);
}

void Quaternion::operator*=(float k)
{
  x *= k;
  y *= k;
  z *= k;
  w *= k;
}

Quaternion Quaternion::operator*(float k) const
{
  return Quaternion(x * k, y * k, z * k, w * k);
}

float Quaternion::length() const
{
  return sqrt(x*x + y*y + z*z + w*w);
}

void Quaternion::convertToUnitNormQuaternion()
{
  float angle = glm::radians(x);
  glm::normalize(getIm());
  x = cos(angle * 0.5f);
  float teta = sin(angle * 0.5f);
  y *= teta;
  z *= teta;
  w *= teta;
}

Quaternion Quaternion::normalize(Quaternion const &quaternion)
{
  float n = quaternion.length();
  if (n != 0)
  {
    return quaternion * (1.0f / n);
  }
  return Quaternion();
}

Quaternion Quaternion::conjugate(Quaternion const &quaternion)
{
  return Quaternion(quaternion.getReal(), quaternion.getIm() * (-1.0f));
}

Quaternion Quaternion::inverse(Quaternion const &quaternion)
{
  float n = quaternion.length();
  n *= n;
  n = 1.0f / n;

  return conjugate(quaternion) * n;
}

void Quaternion::normalize()
{
  *this = normalize(*this); 
}

void Quaternion::inverse()
{
  *this = inverse(*this);
}

void Quaternion::conjugate()
{
  *this = conjugate(*this);
}

float Quaternion::getReal()  const
{
  return x;
}

glm::vec3 Quaternion::getIm() const
{
  return glm::vec3(y, z, w);
}


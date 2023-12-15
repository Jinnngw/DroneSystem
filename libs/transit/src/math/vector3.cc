#include "math/vector3.h"
#include <iostream>
#include <iomanip> // for std::setprecision and std::fixed
#include <sstream> // for std::ostringstream

#define _USE_MATH_DEFINES
#define EPS 0.0000001

/**
 * @brief Default constructor. Initializes to zero vector.
 */
Vector3::Vector3() : Vector3(0) {}
/**
 * @brief Constructor that initializes all components to a single value.
 * @param a Value to initialize all components to.
 */
Vector3::Vector3(double a) : Vector3(a, a, a) {}
/**
 * @brief Constructor with individual component values.
 * @param a X component.
 * @param b Y component.
 * @param c Z component.
 */
Vector3::Vector3(double a, double b, double c) : x(a), y(b), z(c) {}
/**
 * @brief Equality operator.
 * @param v Vector to compare with.
 * @return True if vectors are equal within a small epsilon.
 */
bool Vector3::operator==(const Vector3& v) const {
  return dist(v) < EPS;
}
/**
 * @brief Indexing operator (modifiable).
 * @param i Index of the component.
 * @return Reference to the specified component.
 * @throw std::out_of_range if index is out of range.
 */
double& Vector3::operator[](int i) {
  if(i < 0 || i >= 3) throw std::out_of_range("i not in range for vector");
  switch(i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
  }
  return x;
}
/**
 * @brief Indexing operator (constant).
 * @param i Index of the component.
 * @return Value of the specified component.
 * @throw std::out_of_range if index is out of range.
 */
double Vector3::operator[](int i) const {
  if(i < 0 || i >= 3) throw std::out_of_range("i not in range for vector");
  switch(i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
  }
  return x;
}
/**
 * @brief Adds two vectors.
 * @param v Vector to add.
 * @return Sum of the two vectors.
 */
Vector3 Vector3::operator+(const Vector3& v) const {
  return Vector3(x+v.x, y+v.y, z+v.z);
}
/**
 * @brief Subtracts one vector from another.
 * @param v Vector to subtract.
 * @return Difference of the two vectors.
 */
Vector3 Vector3::operator-(const Vector3& v) const {
  return (*this)+(v*-1);
}
/**
 * @brief Multiplies vector by a scalar.
 * @param s Scalar value.
 * @return Scaled vector.
 */
Vector3 Vector3::operator*(double s) const {
  return Vector3(x*s, y*s, z*s);
}
/**
 * @brief Divides vector by a scalar.
 * @param s Scalar value.
 * @return Scaled vector.
 */
Vector3 Vector3::operator/(double s) const {
  return (*this)*(1/s);
}
/**
 * @brief Dot product of two vectors.
 * @param v Vector to dot with.
 * @return Scalar dot product.
 */
double Vector3::operator*(const Vector3& v) const {
  return x*v.x + y*v.y + z*v.z;
}
/**
 * @brief Cross product of two vectors.
 * @param v Vector to cross with.
 * @return Vector3 representing the cross product.
 */
Vector3 Vector3::cross(const Vector3& v) const {
  return Vector3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}
/**
 * @brief Calculates the magnitude of the vector.
 * @return Magnitude of the vector.
 */
double Vector3::magnitude() const {
  return sqrt(x*x + y*y + z*z);
}
/**
 * @brief Normalizes the vector in-place.
 * @return Reference to the normalized vector.
 */
Vector3& Vector3::normalize() {
  (*this) = unit();
  return *this;
}
/**
 * @brief Returns the unit vector.
 * @return Unit vector.
 */
Vector3 Vector3::unit() const {
  if(magnitude() < EPS) return (*this);
  return (*this)/magnitude();
}
/**
 * @brief Calculates the distance to another vector.
 * @param v Vector to measure distance to.
 * @return Distance to the vector.
 */
double Vector3::dist(const Vector3& v) const {
  return ((*this)-v).magnitude();
}
/**
 * @brief Converts the vector to a string representation.
 * @return String representation of the vector.
 */
std::string Vector3::toString() const {
  std::ostringstream temp;
  temp << std::fixed <<std::setprecision(2);
  temp << "(" << this->x << ", " << this->y << ", " << this->z << ")";

  return temp.str();
}
/**
 * @brief Stream insertion operator for printing vector.
 * @param strm Output stream.
 * @param v Vector to be printed.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& strm, const Vector3& v) {
  strm << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return strm;
}
#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>
#include <iostream>

// a simple class used for vector math, most function are self explanatory
class Vector3 {
  public:
    double x = 0;
    double y = 0;
    double z = 0;
    /**
     * @brief Default constructor.
     */
    Vector3();
    Vector3(double a);
    /**
     * @brief Parameter constructor.
     *
     * @param[in] a x-coordinate
     * @param[in] b y-coordinate
     * @param[in] c z-coordinate
     */
    Vector3(double a, double b, double c);
    bool operator==(const Vector3& v) const;
    double& operator[](int i);
    double operator[](int i) const;
    /**
     * @brief Overrides + operator.
     * @param[in] v The Vector3 object you would like to add to this Vector3
     * object
     * @return The Vector3 Object comprised of the sum of the two objects
     */
    Vector3 operator+(const Vector3& v) const;
    /**
     * @brief Overrides - operator.
     * @param[in] v The Vector3 object you would like to subtract to this Vector3
     * object
     * @return The Vector3 Object comprised of the subtraction of the two objects
     */
    Vector3 operator-(const Vector3& v) const;
    /**
     * @brief Overrides * operator.
     * @param[in] v The Vector3 object you would like to multiply to this Vector3
     * object
     * @return The Vector3 Object comprised of the multiplication of the two
     * objects
     */
    Vector3 operator*(double s) const;
    /**
    * @brief Converts the vector to a string representation.
    * @return String representation of the vector in the format "(x, y, z)".
    */
    std::string toString() const;
    /**
    * @brief Divides the vector by a scalar.
    * @param s Scalar to divide by.
    * @return Vector3 representing the result of the division.
    */
    Vector3 operator/(double s) const;
    /**
    * @brief Dot product of this vector with another vector.
    * @param v Other vector to perform dot product with.
    * @return Dot product as a double.
    */
    double operator*(const Vector3& v) const; //dot product
    /**
    * @brief Cross product of this vector with another vector.
    * @param v Other vector to perform cross product with.
    * @return Vector3 representing the cross product.
    */
    Vector3 cross(const Vector3& v) const;
    /**
    * @brief Calculates the magnitude (length) of the vector.
    * @return Magnitude of the vector.
    */
    double magnitude() const;
    /**
    * @brief Normalizes this vector (makes its magnitude equal to 1).
    * @return Reference to the normalized vector.
    */
    Vector3& normalize();
    /**
    * @brief Calculates the unit vector in the same direction as this vector.
    * @return Unit vector in the same direction.
    */
    Vector3 unit() const; // normal vector in same direction
    /**
    * @brief Calculates the distance from this vector to another vector.
    * @param v Other vector to calculate the distance to.
    * @return Distance to the other vector.
    */
    double dist(const Vector3& v) const;
    friend std::ostream& operator<<(std::ostream& strm, const Vector3& v);
};

#endif

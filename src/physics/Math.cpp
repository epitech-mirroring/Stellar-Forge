/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Vector3f
*/

#include "Math.hpp"
#include <cmath>

Math::Vector3f::Vector3f()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Math::Vector3f::Vector3f(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Math::Vector3f::Vector3f(const Math::Vector3f &vector3f)
{
    this->x = vector3f.x;
    this->y = vector3f.y;
    this->z = vector3f.z;
}

Math::Vector3f::Vector3f(const Math::Vector3f &&vector3f)
{
    this->x = vector3f.x;
    this->y = vector3f.y;
    this->z = vector3f.z;
}

Math::Vector3f &Math::Vector3f::operator=(const Math::Vector3f &vector3f)
{
    this->x = vector3f.x;
    this->y = vector3f.y;
    this->z = vector3f.z;
    return (*this);
}

Math::Vector3f &Math::Vector3f::operator=(const Math::Vector3f &&vector3f)
{
    this->x = vector3f.x;
    this->y = vector3f.y;
    this->z = vector3f.z;
    return (*this);
}

Math::Vector3f Math::Vector3f::operator+(const Math::Vector3f &vector3f) const
{
    return Math::Vector3f(this->x + vector3f.x, this->y + vector3f.y,
                          this->z + vector3f.z);
}

Math::Vector3f &Math::Vector3f::operator+=(const Math::Vector3f &vector3f)
{
    this->x += vector3f.x;
    this->y += vector3f.y;
    this->z += vector3f.z;
    return (*this);
}

Math::Vector3f Math::Vector3f::operator-(const Math::Vector3f &vector3f) const
{
    return Math::Vector3f(this->x - vector3f.x, this->y - vector3f.y,
                          this->z - vector3f.z);
}

Math::Vector3f &Math::Vector3f::operator-=(const Math::Vector3f &vector3f)
{
    this->x -= vector3f.x;
    this->y -= vector3f.y;
    this->z -= vector3f.z;
    return (*this);
}

Math::Vector3f Math::Vector3f::operator*(const Math::Vector3f &vector3f) const
{
    return Math::Vector3f(this->x * vector3f.x, this->y * vector3f.y,
                          this->z * vector3f.z);
}

Math::Vector3f Math::Vector3f::operator*(const double value) const
{
    return Math::Vector3f(this->x * value, this->y * value, this->z * value);
}

Math::Vector3f &Math::Vector3f::operator*=(const Math::Vector3f &vector3f)
{
    this->x *= vector3f.x;
    this->y *= vector3f.y;
    this->z *= vector3f.z;
    return (*this);
}

Math::Vector3f &Math::Vector3f::operator*=(const double value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
    return (*this);
}

Math::Vector3f Math::Vector3f::operator/(const Math::Vector3f &vector3f) const
{
    if (vector3f.x == 0 || vector3f.y == 0 || vector3f.z == 0)
        throw MathDivideByZeroException();
    return Math::Vector3f(this->x / vector3f.x, this->y / vector3f.y,
                          this->z / vector3f.z);
}

Math::Vector3f Math::Vector3f::operator/(const double scalar) const
{
    if (scalar == 0)
        throw MathDivideByZeroException();
    return Math::Vector3f(this->x / scalar, this->y / scalar, this->z / scalar);
}

Math::Vector3f &Math::Vector3f::operator/=(const Math::Vector3f &vector3f)
{
    if (vector3f.x == 0 || vector3f.y == 0 || vector3f.z == 0)
        throw MathDivideByZeroException();
    this->x /= vector3f.x;
    this->y /= vector3f.y;
    this->z /= vector3f.z;
    return (*this);
}

float Math::Vector3f::dot(const Math::Vector3f &vector3f) const
{
    return this->x * vector3f.x + this->y * vector3f.y + this->z * vector3f.z;
}

float Math::Vector3f::length() const
{
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

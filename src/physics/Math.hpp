/*
** EPITECH PROJECT, 2024
** Project
** File description:
** No file there , just an epitech header example .
*/

#ifndef MATH_HPP
#define MATH_HPP



#include <exception>

namespace Math {

    /**
     * @brief Exception thrown when division by zero is attempted.
     */
    class MathDivideByZeroException : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Division by zero.";
        }
    };

    /**
     * @brief Represents a 3f vector.
     */
    class Vector3f {
    public:
        /**
         * @brief Default constructor.
         */
        Vector3f();

        /**
         * @brief Constructor that initializes the vector with the given coordinates.
         * @param x The x-coordinate of the vector.
         * @param y The y-coordinate of the vector.
         * @param z The z-coordinate of the vector.
         */
        Vector3f(double x, double y, double z);

        /**
         * @brief Copy constructor.
         * @param vector3f The vector to be copied.
         */
        Vector3f(const Vector3f &vector3f);

        /**
         * @brief Move constructor.
         * @param vector3f The vector to be moved.
         */
        Vector3f(const Vector3f &&vector3f);

        /**
         * @brief Default destructor.
         */
        ~Vector3f() = default;

        /**
         * @brief Assignment operator.
         * @param vector3f The vector to be assigned.
         * @return Reference to the assigned vector.
         */
        Vector3f &operator=(const Vector3f &vector3f);

        /**
         * @brief Move assignment operator.
         * @param vector3f The vector to be moved.
         * @return Reference to the moved vector.
         */
        Vector3f &operator=(const Vector3f &&vector3f);

        /**
         * @brief Addition operator.
         * @param vector3f The vector to be added.
         * @return The sum of the two vectors.
         */
        Vector3f operator+(const Vector3f &vector3f) const;

        /**
         * @brief Adds a Vector3f to the current vector.
         * @param vector3f The vector to be added.
         * @return Reference to the current vector.
         */
        Vector3f &operator+=(const Vector3f &vector3f);

        /**
         * @brief Subtraction operator.
         * @param vector3f The vector to be subtracted.
         * @return The difference of the two vectors.
         */
        Vector3f operator-(const Vector3f &vector3f) const;

        /**
         * @brief Subtracts a Vector3f from the current vector.
         * @param vector3f The vector to be subtracted.
         * @return Reference to the current vector.
         */
        Vector3f &operator-=(const Vector3f &vector3f);

        /**
         * @brief Multiplication operator.
         * @param vector3f The vector to be multiplied.
         * @return The product of the two vectors.
         */
        Vector3f operator*(const Vector3f &vector3f) const;

        /**
         * @brief Multiplication operator.
         * @param scalar The scalar to be multiplied.
         * @return The product of the vector and the scalar.
         */
        Vector3f operator*(double scalar) const;

        /**
         * @brief Multiplies a Vector3f with the current vector.
         * @param vector3f The vector to be multiplied.
         * @return Reference to the current vector.
         */
        Vector3f &operator*=(const Vector3f &vector3f);

        /**
         * @brief Multiplies the current vector by a scalar.
         * @param scalar The scalar to be multiplied.
         * @return Reference to the current vector.
         */
        Vector3f &operator*=(double scalar);

        /**
         * @brief Division operator.
         * @param vector3f The vector to be divided.
         * @return The quotient of the two vectors.
         */
        Vector3f operator/(const Vector3f &vector3f) const;

        /**
         * @brief Division operator.
         * @param scalar The scalar to be divided.
         * @return The quotient of the vector and the scalar.
         */
        Vector3f operator/(double scalar) const;

        /**
         * @brief Divides the current vector by another vector.
         * @param vector3f The vector to be divided.
         * @return Reference to the current vector.
         */
        Vector3f &operator/=(const Vector3f &vector3f);

        /**
         * @brief Calculates the dot product of two vectors.
         * @param vector3f The vector to be multiplied.
         * @return The dot product of the two vectors.
         */
        float dot(const Vector3f &vector3f) const;

        /**
         * @brief Calculates the length of the vector.
         * @return The length of the vector.
         */
        float length() const;

        float x; /**< The x-coordinate of the vector. */
        float y; /**< The y-coordinate of the vector. */
        float z; /**< The z-coordinate of the vector. */
    };

}


#endif //MATH_HPP

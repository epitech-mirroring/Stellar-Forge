/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** IError
*/

#pragma once

#include <exception>

/**
 * @class IError
 * @brief Interface for error classes
 * @details This interface is used to define the error classes
 * @version 0.1.0
 * @author Marius PAIN
 */
class IError : std::exception
{
public:
 /**
  * @brief Default constructor
  * @details This constructor initializes the error
  * @version 0.1.0
  */
 ~IError() override = default;

 /**
  * @brief Get the error message
  * @details This function returns the error message
  * @return const char*, the error message
  * @version 0.1.0
  */
 [[nodiscard]] const char* what() const noexcept override = 0;
};

/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** UUIDException
*/

#pragma once

#include "IError.hpp"

#include <string>

/**
 * @class UUIDException
 * @brief Exception class for UUID errors
 * @details This class is used to throw UUID errors
 * @version 0.1.0
 * @author Marius PAIN
 */
class UUIDException : public IError
{
public:
 /**
  * @brief Default constructor
  * @details This constructor initializes the UUIDException with a message
  * @param message std::string, the message
  * @version 0.1.0
  */
 explicit UUIDException(const std::string& message);

 /**
  * @brief Default destructor
  * @details This destructor clears the UUIDException
  * @version 0.1.0
  */
 ~UUIDException() override = default;

 /**
  * @brief Get the error message
  * @details This function returns the error message
  * @return const char*, the error message
  * @version 0.1.0
  */
 [[nodiscard]] const char* what() const noexcept override;

private:
 /**
  * @brief The error message
  */
 std::string _message;
};

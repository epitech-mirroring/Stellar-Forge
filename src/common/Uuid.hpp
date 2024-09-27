/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** UUID
*/

#pragma once

#include <uuid/uuid.h>
#include <iostream>

/**
 * @brief UUID class
 *
 * @note This class is used to generate and manage UUIDs
 * @version 0.1.0
 */
class UUID {
public:
    /**
     * @brief Construct a new UUID object
     *
     * @note This constructor creates a new UUID object
     * @version 0.1.0
     */
    UUID();

    /**
     * @brief Destroy the UUID object
     *
     * @note This destructor destroys the UUID object
     * @version 0.1.0
     */
    ~UUID();

    /**
     * @brief Get the UUID
     *
     * @return const uuid_t &, UUID
     * @note This function returns the UUID
     * @version 0.1.0
     */
    const uuid_t &getUuid() const;

    /**
     * @brief Get the UUID as a string
     *
     * @return std::string, UUID as a string
     * @note This function returns the UUID as a string
     * @version 0.1.0
     */
    std::string getUuidString() const;

    /**
     * @brief Generate a new UUID
     *
     * @note This function generates a new UUID
     * @version 0.1.0
     */
    void generateUuid();

    /**
     * @brief Copy a UUID
     *
     * @param uuid uuid_t, UUID to copy
     * @note This function copies a UUID
     * @version 0.1.0
     */
    void copyUuid(uuid_t uuid);

    /**
     * @brief Copy a UUID
     *
     * @param uuid const uuid_t &, UUID to copy
     * @note This function copies a UUID
     * @version 0.1.0
     */
    void copyUuid(const uuid_t &uuid);

    /**
     * @brief Copy a UUID
     *
     * @param uuid UUID, UUID to copy
     * @note This function copies a UUID
     * @version 0.1.0
     */
    void copyUuid(UUID uuid);

    /**
     * @brief Compare a UUID
     *
     * @param uuid uuid_t, UUID to compare
     * @return true, if the UUIDs are equal
     * @return false, if the UUIDs are not equal
     * @note This function compares a UUID
     * @version 0.1.0
     */
    bool compareUuid(uuid_t uuid);

    /**
     * @brief Compare a UUID
     *
     * @param uuid UUID, UUID to compare
     * @return true, if the UUIDs are equal
     * @return false, if the UUIDs are not equal
     * @note This function compares a UUID
     * @version 0.1.0
     */
    bool compareUuid(UUID uuid);

    /**
     * @brief Clear the UUID
     *
     * @note This function clears the UUID and sets it to null
     * @version 0.1.0
     */
    void clearUuid();

    /**
     * @brief Check if the UUID is null
     *
     * @return true, if the UUID is null
     * @return false, if the UUID is not null
     * @note This function checks if the UUID is null
     * @version 0.1.0
     */
    bool isNullUuid();

    /**
     * @brief Set the UUID from a string
     *
     * @param uuid std::string, UUID as a string
     * @note This function sets the UUID from a string
     * @version 0.1.0
     */
    void setUuidFromString(std::string uuid);

    /**
     * @brief Get the UUID as a struct
     *
     * @return const uuid_t &, UUID as a struct
     * @note This function returns the UUID as a struct
     * @version 0.1.0
     */
    const uuid_t &getUuidStruct() const;

    /**
     * @brief Overload the assignment operator
     *
     * @param uuid UUID, UUID to assign
     * @return UUID& , assigned UUID
     * @version 0.1.0
     */
    UUID &operator=(const UUID &uuid);

    /**
     * @brief Overload the assignment operator
     *
     * @param uuid uuid_t, UUID to assign
     * @return UUID& , assigned UUID
     * @version 0.1.0
     */
    UUID &operator=(const uuid_t &uuid);

    /**
     * @brief Overload the equality operator
     *
     * @param uuid UUID, UUID to compare
     * @return true, if the UUIDs are equal
     * @return false, if the UUIDs are not equal
     * @version 0.1.0
     */
    bool operator==(const UUID &uuid);

    /**
     * @brief Overload the equality operator
     *
     * @param uuid uuid_t, UUID to compare
     * @return true, if the UUIDs are equal
     * @return false, if the UUIDs are not equal
     * @version 0.1.0
     */
    bool operator==(const uuid_t &uuid);

    /**
     * @brief Overload the inequality operator
     *
     * @param uuid UUID, UUID to compare
     * @return true, if the UUIDs are not equal
     * @return false, if the UUIDs are equal
     * @version 0.1.0
     */
    bool operator!=(const UUID &uuid);

    /**
     * @brief Overload the inequality operator
     *
     * @param uuid uuid_t, UUID to compare
     * @return true, if the UUIDs are not equal
     * @return false, if the UUIDs are equal
     * @version 0.1.0
     */
    bool operator!=(const uuid_t &uuid);

private:
    // UUID struct (uuid_t)
    uuid_t _uuid;
};

/**
 * @brief Overload the output stream operator
 *
 * @param os std::ostream &, output stream
 * @param uuid UUID, UUID to output
 * @return std::ostream &, output stream
 * @version 0.1.0
 */
std::ostream &operator<<(std::ostream &os, const UUID &uuid);

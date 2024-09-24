/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** EventData
*/

#pragma once

#include <iostream>
#include <functional>

/**
 * @brief Structure to hold event data
 *
 * @param name std::string, name of the event
 * @param timestamp time_t, timestamp of the event
 * @param data void *, data of the event (can be anything)
 * @note This structure is used to pass data to the event consumers
 */
typedef struct EventData_s {
    std::string name;
    time_t timestamp;
    void *data;
} EventData_t;

/**
 * @brief Event consumer function type
 *
 * @param EventData_t * structure containing the event data
 * @note This function type is used to define the event consumers
 */
typedef std::function<void(EventData_t *)> EventConsumer;

/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** Event
*/

#pragma once

#include "EventData.hpp"

#include <vector>
#include <iostream>

/**
 * @brief Event class
 *
 * @note This class is used to create and manage events
 */
class Event {
public:
    /**
     * @brief Construct a new Event object
     *
     * @param name std::string, name of the event
     * @note This constructor creates a new event with the given name
     */
    Event(std::string name);

    /**
     * @brief Destroy the Event object
     *
     * @note This destructor destroys the event
     */
    ~Event();

    /**
     * @brief Add a consumer to the event
     *
     * @param consumer EventConsumer, consumer to add
     * @note This function adds a consumer to the event
     */
    void AddConsumer(EventConsumer consumer);

    /**
     * @brief Remove a consumer from the event
     *
     * @param consumer EventConsumer, consumer to remove
     * @note This function removes a consumer from the event
     */
    void RemoveConsumer(EventConsumer consumer);

    /**
     * @brief Call all consumers of the event
     *
     * @note This function calls all consumers of the event
     */
    void CallConsumers();

protected:
private:
    // Event name (unique identifier)
    std::string _name;
    // Event consumers (callbacks functions)
    std::vector<EventConsumer> _consumers;
};

/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** EventManager
*/

#pragma once

#include "Event.hpp"

#include <unordered_map>

/**
 * @brief Event manager class
 *
 * @note This class is used to manage events
 */
class EventManager {
public:
    /**
     * @brief Construct a new Event Manager object
     *
     * @note This constructor creates a new event manager
     */
    EventManager();

    /**
     * @brief Destroy the Event Manager object
     *
     * @note This destructor destroys the event manager
     */
    ~EventManager();

    /**
     * @brief Add an event to the event manager
     *
     * @param name std::string, name of the event
     * @note This function adds an event to the event manager
     */
    void addEvent(std::string name);

    /**
     * @brief Remove an event from the event manager
     *
     * @param name std::string, name of the event
     * @note This function removes an event from the event manager
     */
    void removeEvent(std::string name);

    /**
     * @brief Add a consumer to an event
     *
     * @param name std::string, name of the event
     * @param consumer EventConsumer, consumer to add
     * @note This function adds a consumer to an event
     */
    void addConsumerToEvent(std::string name, EventConsumer consumer);

    /**
     * @brief Remove a consumer from an event
     *
     * @param name std::string, name of the event
     * @param consumer EventConsumer, consumer to remove
     * @note This function removes a consumer from an event
     */
    void removeConsumerFromEvent(std::string name, EventConsumer consumer);

    /**
     * @brief Call all consumers of an event
     *
     * @param name std::string, name of the event
     * @note This function calls all consumers of an event
     */
    void callConsumersFromEvent(std::string name);

protected:
private:
    // Events map (name -> event)
    std::unordered_map<std::string, Event> _events;
};

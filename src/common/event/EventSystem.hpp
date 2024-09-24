/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** EventSystem
*/

#pragma once

#include "EventManager.hpp"

/**
 * @brief Event system class
 *
 * @note This class is used to create and manage the event system
 */
class EventSystem {
public:
    /**
     * @brief Construct a new Event System object
     *
     * @note This constructor creates a new event system
     */
    EventSystem();

    /**
     * @brief Destroy the Event System object
     *
     * @note This destructor destroys the event system
     */
    ~EventSystem();

    /**
     * @brief Get the event manager
     *
     * @return EventManager *, pointer to the event manager
     * @note This function returns the event manager
     */
    static EventManager *GetEventManager();

private:
    // Event manager instance
    static EventManager *_event_manager;
};

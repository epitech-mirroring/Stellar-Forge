/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** EventSystem
*/

#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP

#include "../UUID.hpp"
#include "EventData.hpp"

/**
 * @brief Event System class
 * @details This class is used to manage events and event listeners
 * @version 0.1.0
 * @since 0.1.0
 * @author Marius PAIN
 */
class EventSystem
{
public:
 /**
  * @brief Default constructor
  * @details This constructor initializes the event system
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 EventSystem();

 /**
  * @brief Copy constructor
  * @details This constructor is deleted
  * @param eventSystem EventSystem, the event system to copy
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 EventSystem(const EventSystem& eventSystem) = delete;

 /**
  * @brief Move constructor
  * @details This constructor is deleted
  * @param eventSystem EventSystem, the event system to move
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 EventSystem(const EventSystem&& eventSystem) noexcept = delete;

 /**
  * @brief Default destructor
  * @details This destructor clears the event system
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 ~EventSystem();

 /**
  * @brief Register a listener for an event
  * @details This function registers a listener for an event
  * @param name std::string, the name of the event
  * @param listener EventConsumer, the listener to register
  * @return UUID, the UUID of the listener
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 UUID registerListener(const std::string& name, const EventConsumer& listener);

 /**
  * @brief Unregister a listener
  * @details This function unregisters a listener
  * @param uuid UUID, the UUID of the listener to unregister
  * @return bool, true if the listener was unregistered,
  * false if the listener was not found
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 bool unregisterListener(const UUID& uuid);

 /**
  * @brief Trigger an event
  * @details This function triggers an event
  * @param eventData EventData_t*, the event data
  * @return bool, true if the event was triggered,
  * false if no listener was found
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 bool triggerEvent(EventData_t* eventData);

 /**
  * @brief Get the event manager
  * @details This function returns the event manager
  * @return EventSystem*, the event manager
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 static EventSystem* getEventManager();

 /**
  * @brief Copy assignment operator
  * @details This operator is deleted
  * @param eventSystem EventSystem, the event system to copy
  * @return EventSystem&, the copied event system
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 EventSystem& operator=(const EventSystem& eventSystem) = delete;

 /**
  * @brief Move assignment operator
  * @details This operator is deleted
  * @param eventSystem EventSystem, the event system to move
  * @return EventSystem&, the moved event system
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 EventSystem& operator=(EventSystem&& eventSystem) noexcept = delete;

private:
 /**
  * @brief Listeners
  * @details This unordered map contains the listeners
  * the key is the name of the event and the value is a vector of pairs
  * that contains the UUID of the listener and the listener itself
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 std::unordered_map<std::string, std::vector<std::pair<UUID, EventConsumer>>> _listeners;

 /**
  * @brief Event manager
  * @details This static pointer contains the event manager
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 static EventSystem* _event_manager;
};

#endif // EVENTSYSTEM_HPP

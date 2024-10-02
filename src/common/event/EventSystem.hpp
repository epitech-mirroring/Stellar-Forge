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
  * @param eventName std::string, the name of the event to trigger
  * @param data void*, the data to pass to the listeners
  * @return bool, true if at least one listener was found,
  * false if no listener was found
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 bool triggerEvents(const std::string& eventName, void* data = nullptr);

 /**
  * @brief Get the instance of the event system
  * @details This function returns an instance of the event system
  * @return EventSystem*, the instance of the event system
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 static EventSystem* getInstance();

private:
 /**
  * @brief Trigger an event from the event name
  * @details This function triggers an event from the event name
  * @param eventName std::string, the name of the event to trigger
  * @param eventData EventData, the data to pass to the listeners
  * @return bool, true if at least one listener was found,
  * false if no listener was found
  * @version 0.1.0
  * @since 0.1.0
  * @author Marius PAIN
  */
 bool _triggerEventFromEventName(const std::string& eventName, const EventData& eventData);

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
 static EventSystem* _event_system;
};

#endif // EVENTSYSTEM_HPP

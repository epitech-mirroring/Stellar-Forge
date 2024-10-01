/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** EventSystem
*/

#include "EventSystem.hpp"

EventSystem::EventSystem(): _listeners({})
{
    _event_manager = this;
}

EventSystem::~EventSystem()
{
    for (auto& listener : this->_listeners)
    {
        listener.second.clear();
    }
    this->_listeners.clear();
}

UUID EventSystem::registerListener(const std::string& name, const EventConsumer& listener)
{
    UUID uuid = UUID();
    uuid.generateUuid();

    if (!this->_listeners.contains(name))
    {
        this->_listeners[name] = std::vector<std::pair<UUID, EventConsumer>>();
    }
    this->_listeners[name].emplace_back(uuid, listener);
    return uuid;
}

bool EventSystem::unregisterListener(const UUID& uuid)
{
    for (auto& listener : this->_listeners)
    {
        for (auto& listener_uuid : listener.second)
        {
            if (listener_uuid.first == uuid)
            {
                std::erase(listener.second, listener_uuid);
                if (listener.second.empty())
                {
                    this->_listeners.erase(listener.first);
                }
                return true;
            }
        }
    }
    return false;
}

bool EventSystem::triggerEvent(EventData_t* eventData)
{
    bool triggered = false;

    if (this->_listeners.contains(eventData->name))
    {
        for (auto& listener : this->_listeners[eventData->name])
        {
            listener.second(eventData);
            triggered = true;
        }
    }
    return triggered;
}

EventSystem* EventSystem::getEventManager()
{
    if (_event_manager == nullptr)
    {
        return nullptr;
    }
    return _event_manager;
}

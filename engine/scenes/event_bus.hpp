#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>
#include <any>

class EventBus
{
public:
    using EventHandler = std::function<void(std::any)>;

    EventBus() = default;

    void Subscribe(const std::string &eventType, EventHandler handler)
    {
        listeners[eventType].push_back(handler);
    }

    void Publish(const std::string &eventType, std::any data = {})
    {
        if (listeners.count(eventType))
        {
            for (const auto &handler : listeners[eventType])
            {
                handler(data);
            }
        }
    }

private:
    std::map<std::string, std::vector<EventHandler>> listeners;
};

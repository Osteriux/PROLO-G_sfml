#include "game_event_system.hpp"
#include <algorithm>
#include <iostream>

// Initialize static instance pointer
GameEventSystem *GameEventSystem::instance = nullptr;

void GameEventSystem::initialize()
{
    if (instance != nullptr)
    {
        throw std::runtime_error("GameEventSystem already initialized");
    }
    instance = new GameEventSystem();
}

GameEventSystem &GameEventSystem::getInstance()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("GameEventSystem not initialized. Call initialize() first.");
    }
    return *instance;
}

void GameEventSystem::destroy()
{
    delete instance;
    instance = nullptr;
}

void GameEventSystem::subscribe(GameEvent::Type type, IEventListener *listener)
{
    if (listener == nullptr)
    {
        std::cerr << "Warning: Attempted to subscribe null listener" << std::endl;
        return;
    }

    auto &list = listeners[type];
    // Avoid duplicate subscriptions
    if (std::find(list.begin(), list.end(), listener) == list.end())
    {
        list.push_back(listener);
    }
}

void GameEventSystem::unsubscribe(GameEvent::Type type, IEventListener *listener)
{
    auto it = listeners.find(type);
    if (it != listeners.end())
    {
        auto &list = it->second;
        list.erase(std::remove(list.begin(), list.end(), listener), list.end());
    }
}

void GameEventSystem::unsubscribeAll(IEventListener *listener)
{
    for (auto &[type, list] : listeners)
    {
        list.erase(std::remove(list.begin(), list.end(), listener), list.end());
    }
}

void GameEventSystem::dispatch(const GameEvent &event)
{
    auto it = listeners.find(event.getType());
    if (it != listeners.end())
    {
        // Create a copy of the listener list to allow safe modifications during iteration
        ListenerList listenersCopy = it->second;
        for (auto *listener : listenersCopy)
        {
            listener->onEvent(event);
        }
    }
}

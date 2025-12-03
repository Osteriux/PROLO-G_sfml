#pragma once
#include "game_event.hpp"
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

// Event listener interface
class IEventListener
{
public:
    virtual ~IEventListener() = default;
    virtual void onEvent(const GameEvent &event) = 0;
};

// Event system - singleton pattern for global access
class GameEventSystem
{
private:
    using ListenerList = std::vector<IEventListener *>;
    std::unordered_map<GameEvent::Type, ListenerList> listeners;

    static GameEventSystem *instance;
    GameEventSystem() = default;

public:
    static void initialize();
    static GameEventSystem &getInstance();
    static void destroy();

    // Subscribe a listener to specific event types
    void subscribe(GameEvent::Type type, IEventListener *listener);

    // Unsubscribe a listener from specific event types
    void unsubscribe(GameEvent::Type type, IEventListener *listener);

    // Unsubscribe a listener from all event types
    void unsubscribeAll(IEventListener *listener);

    // Dispatch an event to all registered listeners
    void dispatch(const GameEvent &event);

    ~GameEventSystem() = default;

    // Delete copy constructor and assignment operator
    GameEventSystem(const GameEventSystem &) = delete;
    GameEventSystem &operator=(const GameEventSystem &) = delete;
};

#pragma once
#include "../Framework/Source/Events/Event.h"
#include "Events/GameEventTypes.h"

enum GameEventTypes
{
    GameEventType_RemoveFromScene = 0,
    GameEventType_PlayerFire,
    GameEventType_MAX
};

class Scene;
class GameObject;

class GameEvent : public Event
{
    GameEventTypes m_GameEventType;

public:
    GameEvent(GameEventTypes type)
    {
        m_GameEventType = type;
    }

    virtual EventTypes GetEventType() override { return EventType_GamePlay; }
    virtual GameEventTypes GetGameEventType() { return m_GameEventType; };
};
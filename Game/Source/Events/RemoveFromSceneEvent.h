#ifndef __RemoveFromSceneEvent_H__
#define __RemoveFromSceneEvent_H__

#include "GameEvent.h"


class RemoveFromSceneEvent : public Event
{
protected:
    Scene * m_pScene;
    GameObject* m_pGameObject;

public:
    RemoveFromSceneEvent(Scene* pScene, GameObject* gameobject)
    {
        m_pScene = pScene;
        m_pGameObject = gameobject;
    }
    virtual EventTypes GetEventType() override { return EventType_RemoveFromScene; }

    Scene* GetScene() { return m_pScene; }
    GameObject* GetGameObject() { return m_pGameObject; }
};

#endif //__RemoveFromSceneEvent_H__
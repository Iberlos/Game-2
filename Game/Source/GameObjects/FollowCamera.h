#ifndef __FollowCamera_H__
#define __FollowCamera_H__

#include "GameObjects/CameraObject.h"

class FollowCamera : public CameraObject
{
public:
    FollowCamera(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, float a_followDistance, GameObject* a_target);
    ~FollowCamera();
    void Update(float deltaTime) override;

    virtual void OnEvent(Event* pEvent) override;

protected:
    float m_followDistance;
    GameObject* m_target;
    vec2 m_LastMousePosition;
};

#endif
#pragma once

#include "GameObjects/GameObject.h"

class GunObject : public GameObject
{
    const float ANIM_TIME = 0.05f;

public:
    GunObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~GunObject();

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;

    virtual void GenerateImGuiWindow() override;

protected:
    int m_WhichTween;
    TweenFunction* m_TweenFunction;
    float m_TimeRemaining;
    float m_KickTime;
    float m_ResetTime;

};
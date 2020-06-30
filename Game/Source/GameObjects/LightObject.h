#pragma once
#include "GameObject.h"

class Light : public GameObject
{
public:
    Light(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);

    vec3 GetColor() { return m_color; }
    float GetFalloff() { return m_falloff; }
    bool GetIsActive() { return m_IsActive; }

    void SetIsActive(bool isActive) { m_IsActive = isActive; }
    void SetTarget(GameObject* a_Target) { m_Target = a_Target; }
    void SetFalloff(float falloff) { m_falloff = falloff; }

    virtual void Update(float deltaTime) override;
    virtual void Draw(CameraObject* pCamera) override;
    virtual void GenerateImGuiWindow() override;

protected:
    vec3 m_color;
    float m_falloff;
    bool m_IsActive;
    GameObject* m_Target;
    float m_FollowDistance;
};
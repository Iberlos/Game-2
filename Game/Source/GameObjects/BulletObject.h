#pragma once
#include "GameObject.h"

class BulletObject : public GameObject
{
    const float BULLET_LIFETIME = 0.2f;

public:
    BulletObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    ~BulletObject();

    virtual void Update(float deltaTime) override;
    virtual void Draw(CameraObject* pCamera) override;

    void SetColor(vec4 color) { m_Color = color; }

protected:
    float m_LifeTimeTimer;
    vec4 m_Color;
};
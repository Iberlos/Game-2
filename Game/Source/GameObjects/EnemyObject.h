#pragma once

#include "GameObjects/GameObject.h"

class EnemyObject : public GameObject
{
    const float FIRE_RANGE = 500.0f; //Distance to fore
    const float MOVE_DISTANCE = 1.0f; //Distance to move when in move mode
    const float ROTATE_AMOUNT = 30.0f; //Degrees to rotate on each axis

    enum  EnemyMode
    {
        EnemyMode_Move,
        EnemyMode_Wait,
        EnemyMode_Shoot,
        EnemyMode_MAX
    };

public:
    EnemyObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    ~EnemyObject();

    virtual void Reset() override;

    virtual void Update(float deltaTime) override;

    void Die();

protected:
    void Fire();

    //"AI" functions
    typedef void (EnemyObject::*AIFunctionPtr)();
    void Move();
    void Wait();
    void Shoot();
    AIFunctionPtr m_Modes[3];
    bool m_ModeDone;
    int m_NumOfActions;
    int m_CurrentMode;
    float m_Damage;
    vec4 m_BulletColor;
};
#ifndef __Player_H__
#define __Player_H__

#include "GameObjects/GameObject.h"

class Mesh;
class PlayerController;
class SoundObject;

//So it's accessible to other stuff
const float MOUSE_ROT_SPEED = 0.05f;

class Player : public GameObject
{
    const float PLAYER_SPEED = 150.0f;   // Units per second
    const float JUMP_SPEED = 300.0f;
    const float FIRE_SPEED = 0.25f;
    const float FIRE_RANGE = 500.0f;
    const int STARTING_AMMO = 6;
    const float STARTING_HEALTH = 100;

protected:
    PlayerController* m_pPlayerController;
    vec2 m_LastMousePosition;
    CameraObject* m_FirstPersonCamera;

    //Movement stuff
    float m_Speed;
    float m_TurningSpeed;
    bool m_bHasJump;

    btVector3 ImpulseToAchieveVelocity(vec3 a_velocity, bool a_ignoreXaxis, bool a_ignoreYaxis);
    btVector3 ImpulseToAchieveAngularVelocity(vec3 a_angularVelocity);

    //weapon stuff
    float m_FireDelay;
    float m_FireSpeed;
    std::string m_ShotObject;
    int m_Ammo;
    vec4 m_BulletColor;

    void Fire();

    //Health stuff
    float m_CurrentHealth;


    //Score stuff
    float m_CurrentScore;
public:
    Player(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~Player();

    virtual void Reset() override;
    virtual void Update(float deltaTime) override;

    void SetPlayerController(PlayerController* controller) { m_pPlayerController = controller; }
    void SetSpeed(float speed) { m_Speed = speed; }
    void SetTurningSpeed(float speed) { m_TurningSpeed = speed; }
    void SetFirstPersonCamera(CameraObject* camera) { m_FirstPersonCamera = camera; }

    virtual void GenerateImGuiWindow() override;

    virtual void OnContactStarted(GameObject* otherObject, vec3 worldNormal) override;


    virtual void OnEvent(Event* pEvent) override;

    void TakeDamage(float a_amount);
    float GetHealthPercent() { return m_CurrentHealth / STARTING_HEALTH; }
};

#endif //__Player_H__

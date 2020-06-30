#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/EnemyObject.h"
#include "Player.h"
#include "Game/Scene.h"
#include "Scenes/MainGameScene.h"
#include "Physics3D/PhysicsManager.h"
#include "Audio/SoundCue.h"
#include "Audio/SoundPlayer.h"
#include "Game/ResourceManager.h"
#include "Events/GameEvent.h"
#include "Game/SceneManager.h"


Player::Player(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
, m_pPlayerController( nullptr )
, m_Speed( PLAYER_SPEED )
, m_TurningSpeed(100.0f)
, m_FireSpeed(FIRE_SPEED)
, m_Ammo(STARTING_AMMO)
, m_FireDelay(-1.0f)
, m_LastMousePosition(0,0)
, m_CurrentHealth(STARTING_HEALTH)
{
    m_Tags.push_back("Player");
    m_DebugDraw = true;
    m_bHasJump = true;
    m_FirstPersonCamera = nullptr;
    m_BulletColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
    
Player::~Player()
{
}

void Player::Reset()
{
    GameObject::Reset();
    m_CurrentHealth = STARTING_HEALTH;
    m_Ammo = STARTING_AMMO;
    m_CurrentScore = 0;
}

void Player::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    //IF PLAYER HAS FALLEN FROM THE PLATFORM KILL HIM
    if (m_Position.y <=-10)
    {
        TakeDamage(100);
    }

    vec3 dir( 0, 0, 0 );
    vec3 rotDir(0, 0, 0);
    if (m_pPlayerController)
    {

        //Rotation
        if (m_pPlayerController->IsHeld_Rotate_C())
        {
            rotDir.y = 1;
        }
        if (m_pPlayerController->IsHeld_Rotate_CC())
        {
            rotDir.y = -1;
        }

        //Movement
        if (m_pPlayerController->IsHeld_Up())
        {
            dir.z = 1;
        }

        if (m_pPlayerController->IsHeld_Down())
        {
            dir.z = -1;
        }

        if (m_pPlayerController->IsHeld_Left())
        {
            dir.x = -1;
        }

        if( m_pPlayerController->IsHeld_Right() )
        {
            dir.x = 1;
        }

        if (m_pPlayerController->IsHeld_Shoot())
        {
            if (m_FireDelay <= 0.0f)
            {
                Event* pEvent = new GameEvent(GameEventType_PlayerFire);
                m_pScene->GetGame()->GetEventManager()->QueueEvent(pEvent);
            }
        }

        if (m_pPlayerController->IsHeld_Jump())
        {
            if (m_bHasJump)
            {
                m_bHasJump = false;
                m_Body->applyCentralImpulse(ImpulseToAchieveVelocity(vec3(0,1,0)*JUMP_SPEED * deltaTime, true, false));
                m_pScene->GetResourceManager()->GetSoundCue("JumpVocalCue")->Play();
            }
        }
    }

    if (m_FireDelay > 0.0f)
    {
        m_FireDelay -= deltaTime;
        if (m_FireDelay < 0.0f)
        {
            m_ShotObject = "";
        }
    }
    
    m_Body->activate(true);

    dir.Normalize();
    //Align to game object's forward direction
    dir = m_ForwardVector * dir.z - m_ForwardVector.Cross(vec3(0.0f, 1.0f, 0.0f))*dir.x;
    //apply impulse in the correct directions
    m_Body->applyCentralImpulse(ImpulseToAchieveVelocity(dir*m_Speed * deltaTime, false, true));

}

void Player::GenerateImGuiWindow()
{
    ImGui::Begin("GameObjects");
    std::string title;
    if (ImGui::CollapsingHeader(m_Name.c_str()))
    {
        ImGui::Indent();
        ImGui::PushID(this);

        if (ImGui::CollapsingHeader("Transform"))
        {
            ImGui::Indent();
            ImGui::DragFloat3("Scale", &m_Scale.x);
            ImGui::DragFloat3("Rotation", &m_Rotation.x);
            ImGui::DragFloat3("Position", &m_Position.x);
            ImGui::Unindent();
        }
        if (ImGui::CollapsingHeader("Movement"))
        {
            ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 10000.0f);
            ImGui::SliderFloat("AngularSpeed", &m_TurningSpeed, 0.0f, 3600.0f);
        }
        if (m_Body)
        {
            if (ImGui::CollapsingHeader("Physics3D Body"))
            {
                title = "Velocity: " + std::to_string(m_Body->getLinearVelocity().x()) + ", " + std::to_string(m_Body->getLinearVelocity().y()) + ", " + std::to_string(m_Body->getLinearVelocity().z());
                if (ImGui::CollapsingHeader(title.c_str()))
                {
                    ImGui::Text("Vel X: %f", m_Body->getLinearVelocity().x());
                    ImGui::Text("Vel Y: %f", m_Body->getLinearVelocity().y());
                    ImGui::Text("Vel Z: %f", m_Body->getLinearVelocity().z());
                }
                title = "Angular Velocity: " + std::to_string(m_Body->getAngularVelocity().x()) + ", " + std::to_string(m_Body->getAngularVelocity().y()) + ", " + std::to_string(m_Body->getAngularVelocity().z());
                if (ImGui::CollapsingHeader(title.c_str()))
                {
                    ImGui::Text("AVel X: %f", m_Body->getAngularVelocity().x());
                    ImGui::Text("AVel Y: %f", m_Body->getAngularVelocity().y());
                    ImGui::Text("AVel Z: %f", m_Body->getAngularVelocity().z());
                }
                if (ImGui::CollapsingHeader("Mass Properties"))
                {
                    ImGui::Text("Mass: %f", m_Body->getInvMass());
                    ImGui::Text("Inertia X: %f", m_Body->getLocalInertia().x());
                    ImGui::Text("Inertia X: %f", m_Body->getLocalInertia().y());
                    ImGui::Text("Inertia X: %f", m_Body->getLocalInertia().z());
                }
                if (ImGui::CollapsingHeader("Collision Properties"))
                {
                    ImGui::Text("Static: %d", m_Body->isStaticObject());
                    ImGui::Text("Kinematic: %d", m_Body->isKinematicObject());
                    ImGui::Text("In world: %d", m_Body->isInWorld());
                }
            }
        }
        if (ImGui::CollapsingHeader("Handgun"))
        {
            ImGui::ColorPicker4("Bullet Color", &m_BulletColor.x);
            ImGui::SliderFloat("FireSpeed", &m_FireSpeed, 0.0f, 10.0f);
            ImGui::Text("Time remaining until Fire-able: %f", m_FireDelay);
            ImGui::Text("LastShotObject: %s", m_ShotObject.c_str());
            ImGui::Text("Remaining Ammo: %d", m_Ammo);
        }

        ImGui::PopID();
        ImGui::Unindent();
    }
    ImGui::End();
}

void Player::OnContactStarted(GameObject* otherObject, vec3 worldNormal)
{
    if (otherObject->ObjectHasTag("Ground"))
    {
        if (worldNormal.y > 0.0f)
        {
            //set bCanJump to true
            m_bHasJump = true;
        }
    }
    else if (otherObject->ObjectHasTag("Pickup"))
    {
        m_Ammo = 6;
    }
}

void Player::OnEvent(Event* pEvent)
{
    if (pEvent->GetEventType() == EventType_Input)
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);
        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse)
        {
            int buttonID = pInput->GetID();
            if (pInput->GetInputState() == InputState_Held)
            {
                int screenMidX = static_cast<int>(m_pScene->GetGame()->GetFramework()->GetWindowWidth() * 0.5f);
                int screenMidY = static_cast<int>(m_pScene->GetGame()->GetFramework()->GetWindowHeight() * 0.5f);

                m_Body->activate(true);
                float mouseDifX = pInput->GetPosition().x - (float)screenMidX;
                m_Body->applyTorqueImpulse(ImpulseToAchieveAngularVelocity(vec3(0.0f, mouseDifX * MOUSE_ROT_SPEED, 0.0f)));
                m_LastMousePosition = pInput->GetPosition();
            }
        }
        else if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard)
        {
            int keyID = pInput->GetID();

            if (pInput->GetInputState() == InputState_Pressed)
            {
                //Nothing to see here
            }
        }
#endif
    }
    else if (pEvent->GetEventType() == EventType_GamePlay)
    {
        GameEvent* pGameEvent = static_cast<GameEvent*>(pEvent);
        if (pGameEvent->GetGameEventType() == GameEventType_PlayerFire)
        {
            Fire();
        }
    }
}

void Player::TakeDamage(float a_amount)
{
    m_CurrentHealth -= a_amount;
    m_pScene->GetResourceManager()->GetSoundCue("HurtCue")->Play();
    if (m_CurrentHealth <= 0.0f)
    {
        m_pScene->GetGame()->GetSceneManager()->PushScene("GameOverScene");
    }
}

btVector3 Player::ImpulseToAchieveVelocity(vec3 a_velocity, bool a_ignoreMoveaxis, bool a_ignoreJumpaxis)
{
    vec3 targetVelocity = a_velocity;
    vec3 currentVelocity = vec3(m_Body->getLinearVelocity().x(), m_Body->getLinearVelocity().y(), m_Body->getLinearVelocity().z());
    float mass = m_Body->getInvMass();
    if (a_ignoreMoveaxis)
    {
        targetVelocity.x = currentVelocity.x;
        targetVelocity.z = currentVelocity.z;
    }
    if (a_ignoreJumpaxis)
    {
        targetVelocity.y = currentVelocity.y;
    }
    vec3 impulse = mass * (targetVelocity - currentVelocity);

    btVector3 returnValue = btVector3(impulse.x, impulse.y, impulse.z);
    return returnValue;
}

btVector3 Player::ImpulseToAchieveAngularVelocity(vec3 a_velocity)
{
    vec3 targetVelocity = a_velocity;
    vec3 currentVelocity = vec3(m_Body->getAngularVelocity().x(), m_Body->getAngularVelocity().y(), m_Body->getAngularVelocity().z());
    float inertia = m_Body->getLocalInertia().y();

    //targetVelocity.x = currentVelocity.x;
    //targetVelocity.z = currentVelocity.z;

    vec3 impulse = inertia * (targetVelocity - currentVelocity);

    btVector3 returnValue = btVector3(impulse.x, impulse.y, impulse.z);
    return returnValue;
}

void Player::Fire()
{
    if (m_FireDelay < 0.0f)
    {
        m_FireDelay = m_FireSpeed;
        if (m_Ammo > 0)
        {
            m_Ammo--;

            vec3 forwardVec = m_ForwardVector;
            if (m_FirstPersonCamera)
            {
                forwardVec = m_FirstPersonCamera->GetForwardVector();
            }

            //And do some firing
            btCollisionWorld::ClosestRayResultCallback shootResult(btVector3(m_Position.x, m_Position.y, m_Position.z), btVector3(forwardVec.x, forwardVec.y, forwardVec.z) * FIRE_RANGE);

            m_pScene->GetPhysicsManager()->GetWorld()->rayTest(btVector3(m_Position.x, m_Position.y, m_Position.z), btVector3(forwardVec.x, forwardVec.y, forwardVec.z) * FIRE_RANGE, shootResult);

            if (shootResult.hasHit())
            {
                GameObject* hitObject = static_cast<GameObject*>(shootResult.m_collisionObject->getUserPointer());
                m_ShotObject = hitObject->GetName();
                if (hitObject->ObjectHasTag("Enemy"))
                {
                    EnemyObject* enemy = dynamic_cast<EnemyObject*>(hitObject);
                    enemy->Die();
                    m_CurrentScore += 10;
                }
            }
            //Spawn our bullet
            MainGameScene* gameScene = dynamic_cast<MainGameScene*>(m_pScene);
            if (gameScene)
            {
                vec3 rot = m_FirstPersonCamera->GetRotation();

                float distance = (vec3(shootResult.m_hitPointWorld) - m_Position).Length();

                gameScene->SpawnBullet(m_Position, rot, distance, m_BulletColor); //this needed a distance so we can scale the cilinder to reach the target.
            }
            //Play gun shot sound
            m_pScene->GetResourceManager()->GetSoundCue("GunShotCue")->Play();
        }
        else
        {
            //Play gun empty
            m_pScene->GetResourceManager()->GetSoundCue("EmptyGunShotCue")->Play();
        }
    }
}

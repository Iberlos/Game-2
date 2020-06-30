#include "GamePCH.h"
#include "EnemyObject.h"
#include "Player.h"
#include "Game/Scene.h"
#include "Scenes/MainGameScene.h"
#include "Physics3D/PhysicsManager.h"
#include "Game/ResourceManager.h"
#include "Events/RemoveFromSceneEvent.h"
#include "Game/Game.h"


EnemyObject::EnemyObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_Tags.push_back("Enemy");

    m_Modes[EnemyMode_Move] = &EnemyObject::Move;
    m_Modes[EnemyMode_Wait] = &EnemyObject::Wait;
    m_Modes[EnemyMode_Shoot] = &EnemyObject::Shoot;
    m_CurrentMode = EnemyMode_Move;//EnemyMode_Move;
    m_NumOfActions = 3;
    m_ModeDone = false;
    m_Damage = 5;
    m_BulletColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::Reset()
{
    //SetPosition to a safe position (Initial position)
    SetPosition(m_InitialPosition);

    m_CurrentMode = EnemyMode_Move;;

    //Queue this object to be removed from the scene
    Event* destroy = new RemoveFromSceneEvent(m_pScene, this);
    m_pScene->GetGame()->GetEventManager()->QueueEvent(destroy);
}

void EnemyObject::Update(float deltaTime)
{
    GameObject::Update(deltaTime);
    (this->*(m_Modes[m_CurrentMode]))();
}

void EnemyObject::Fire()
{
    vec3 forwardVec = m_ForwardVector;

    //And do some firing
    btCollisionWorld::ClosestRayResultCallback shootResult(btVector3(m_Position.x, m_Position.y, m_Position.z), btVector3(forwardVec.x, forwardVec.y, forwardVec.z) * FIRE_RANGE);

    m_pScene->GetPhysicsManager()->GetWorld()->rayTest(btVector3(m_Position.x, m_Position.y, m_Position.z), btVector3(forwardVec.x, forwardVec.y, forwardVec.z) * FIRE_RANGE, shootResult);

    if (shootResult.hasHit())
    {
        if (static_cast<GameObject*>(shootResult.m_collisionObject->getUserPointer())->ObjectHasTag("Player"))
        {
            Player* player = static_cast<Player*>(shootResult.m_collisionObject->getUserPointer());
            player->TakeDamage(m_Damage);
        }
    }
    //Spawn our bullet
    MainGameScene* gameScene = dynamic_cast<MainGameScene*>(m_pScene);
    if (gameScene)
    {
        vec3 rot = GetRotation();

        float distance = (vec3(shootResult.m_hitPointWorld) - m_Position).Length();
        gameScene->SpawnBullet(m_Position, rot, distance, m_BulletColor); //this needed a distance so we can scale the cylinder to reach the target.
    }
    //Play ray sound
    m_pScene->GetResourceManager()->GetSoundCue("EnemyRayCue")->Play();
}

void EnemyObject::Die()
{
    //Play death sound
    m_pScene->GetResourceManager()->GetSoundCue("EnemyDeathCue")->Play();

    //Reset
    Reset();
}

void EnemyObject::Move()
{
    //if there are no tween functions running (size is zero) and the mode is not done
    if (m_Tweens.size() == 0)
    {
        if (!m_ModeDone)
        {
            //Randomly choose a spot in a certain distance and push a tween function to move you there
            vec3 moveTarget = (vec3((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50)).Normalize())*MOVE_DISTANCE;

            //mark mode as done
            m_ModeDone = true;
        }
        //else
        else
        {
            //reset mode done
            m_ModeDone = false;
            //randomly choose another mode to go to
            m_CurrentMode = EnemyMode_Wait;//rand() % 3;
        }
        //
    }

}

void EnemyObject::Wait()
{
    //if there are no tween functions running (size is zero)
    if (m_Tweens.size() == 0)
    {
        if (!m_ModeDone)//If the mode is not done
        {
            //Randomly rotate on axis
            vec3 rotateTarget = (vec3((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), 0.0f).Normalize())*ROTATE_AMOUNT; //No point in rolling
            AddRotationTween(TweenFunc_SineEaseOut, rotateTarget, 1.0f);

            //reduce the number of actions
            m_NumOfActions--;
            //if there are no more actions to take
            if (m_NumOfActions <= 0)
            {
                //mark mode as done
                m_ModeDone = true;
            }
        }
        //else
        else
        {
            //reset mode done
            m_ModeDone = false;
            //reset num of actions
            m_NumOfActions = 3;
            //randomly choose another mode to go to
            m_CurrentMode = EnemyMode_Shoot;
        }
        //
    }

}

void EnemyObject::Shoot()
{
    //if there are no tween functions running (size is zero) and the mode is not done
    if (m_Tweens.size() == 0 )
    {
        if (!m_ModeDone)
        {
            //Get player's position
            GameObject* player = m_pScene->GetGameObjectByName("Player");
            vec3 targetPos = player->GetPosition();

            //Rotate on axis to face the player
            vec3 targetDirection = (targetPos - m_Position).Normalize();
            float angleYaw = atan2f(targetDirection.z, targetDirection.x) * (180.0f / PI);
            float anglePitch = atan2f(targetDirection.y, sqrtf(targetDirection.x* targetDirection.x + targetDirection.z * targetDirection.z)) * (180.0f / PI);
            //+90 for reasons
            vec3 rotateTarget = vec3(anglePitch, angleYaw - 90.0F, 0.0f);
            //SetRotation(rotateTarget);
            AddRotationTween(TweenFunc_SineEaseOut, rotateTarget - m_Rotation, 1.0f);

            //mark mode as done
            m_ModeDone = true;
        }
        //else
        else
        {
            //Shoot
            Fire();
            //reset mode done
            m_ModeDone = false;
            //randomly choose another mode to go to
            m_CurrentMode = EnemyMode_Move;//rand() % 3;
        }
        //
    }

}

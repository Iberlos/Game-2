#include "GamePCH.h"
#include "MainGameScene.h"

#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/SceneManager.h"
#include "Game/Scene.h"
#include "GameObjects/BulletObject.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/FollowCamera.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/EnemyObject.h"
#include "GameObjects/PickupObject.h"
#include "Physics3D/PhysicsManager.h"
#include "GameObjects/LightObject.h"
#include "FBOs/FBODefinition.h"
#include "UI/SwitchScreenButton.h"

MainGameScene::MainGameScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
: Scene(a_Name, pGame, pResources, pPlayer )
{
    SetDificulty(DE_Easy);
    m_EnemySpawnTimer = ENEMY_SPAWN_DELAY;
}

MainGameScene::~MainGameScene()
{
    //CALL CLEANUP FIRST
    delete m_BulletPool;
    delete m_EnemyPool;
}

void MainGameScene::OnFocusOn()
{
    while (ShowCursor(false) >= 0);

    int screenMidX = static_cast<int>(GetGame()->GetFramework()->GetWindowWidth() * 0.5f);
    int screenMidY = static_cast<int>(GetGame()->GetFramework()->GetWindowHeight() * 0.5f);
    GetGame()->GetFramework()->SetMousePosition(ivec2(screenMidX, screenMidY));
}

void MainGameScene::LoadContent()
{
    Scene::LoadContent();

    //Setup physics Scene
    {
        m_PhysicsManager = new PhysicsManager;
        m_PhysicsManager->SetDebugDrawMat(m_pResources->GetMaterial("FlatColor"));
    }

    // Create our GameObjects.
    {
        //player
        Player* pPlayer = new Player(this, "Player", vec3(0, 3.0f, 0), vec3(0, 0, 0), vec3(1, 1, 1), nullptr, nullptr);
        btRigidBody* playerBody = pPlayer->AddRigidBody(m_pResources->GetCollisionShape("1x1x1 Box"), 1.0f, true);
        pPlayer->AddTag("Player");
        AddGameObject(pPlayer);
#undef new
            //Hinge stuff
        //m_PlayerConstraint = new btGeneric6DofConstraint(*playerBody, btVector3(1,1,1), btVector3(0, 1, 0));
        //m_PhysicsManager->GetWorld()->addConstraint(m_PlayerConstraint);
#define new new(__FILE__, __LINE__)

        // Camera.
        CameraObject* pCamera = new FollowCamera(this, "Camera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1), 0.4f, pPlayer);
        AddGameObject(pCamera);

        pPlayer->SetFirstPersonCamera(pCamera);
        m_PhysicsManager->SetDebugCamera(pCamera);

        // Assign our controllers.
        pPlayer->SetPlayerController(m_pGame->GetController(0));

        //Layout the map
        //Main Plane
        GameObject* Ground = new GameObject(this, "Ground1", vec3(0.0f, -7.5f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(10.0f, 10.0f, 10.0f), m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("StoneWall"));
        Ground->AddRigidBody(m_pResources->GetCollisionShape("10x10x10 Box"), 0.0f);
        Ground->AddTag("Ground");
        AddGameObject(Ground);
        //Step 1
        Ground = new GameObject(this, "Ground2", vec3(-2.5f, -6.5f, 7.5f), vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 10.0f, 5.0f), m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("StoneWall"));
        Ground->AddRigidBody(m_pResources->GetCollisionShape("5x10x5 Box"), 0.0f);
        Ground->AddTag("Ground");
        AddGameObject(Ground);
        //Step 2
        Ground = new GameObject(this, "Ground3", vec3(-7.5f, -5.5f, 7.5f), vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 10.0f, 5.0f), m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("StoneWall"));
        Ground->AddRigidBody(m_pResources->GetCollisionShape("5x10x5 Box"), 0.0f);
        Ground->AddTag("Ground");
        AddGameObject(Ground);
        //Step 3
        Ground = new GameObject(this, "Ground4", vec3(-7.5f, -4.5f, 2.5f), vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 10.0f, 5.0f), m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("StoneWall"));
        Ground->AddRigidBody(m_pResources->GetCollisionShape("5x10x5 Box"), 0.0f);
        Ground->AddTag("Ground");
        AddGameObject(Ground);
        //Step 4
        Ground = new GameObject(this, "Ground5", vec3(-7.5f, -3.5f, -2.5f), vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 10.0f, 5.0f), m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("StoneWall"));
        Ground->AddRigidBody(m_pResources->GetCollisionShape("5x10x5 Box"), 0.0f);
        Ground->AddTag("Ground");
        AddGameObject(Ground);

        GameObject* Cube = new PickupObject(this, "Cube", vec3(-7.5f, 2.0f, -2.5f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f), m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("PlyWood"));
        Cube->AddRigidBody(m_pResources->GetCollisionShape("1x1x1 Box"));
        Cube->AddTag("Pickup");
        AddGameObject(Cube);


        //Object pools
        //Bullets
        m_BulletPool = new ObjectPool<GameObject *>();
        for (unsigned int i = 0; i < MAX_BULLETS_IN_POOL; i++)
        {
            GameObject* bullet = new BulletObject(this, "Bullet" + std::to_string(i), vec3(0), vec3(0), vec3(1.0f), m_pResources->GetMesh("Cylinder"), m_pResources->GetMaterial("Color"));
            m_BulletPool->AddNewObjectToPool(bullet);
            bullet->SetPool(m_BulletPool);
        }
        //Enemies
        m_EnemyPool = new ObjectPool<GameObject *>();
        for (unsigned int i = 0; i < MAX_ENEMIES_IN_POOL; i++)
        {
            GameObject* Enemy = new EnemyObject(this, "Enemy" + std::to_string(i), vec3(0.0f, -50.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f), m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("Eye"));
            Enemy->AddRigidBody(m_pResources->GetCollisionShape("0.5f Sphere"), 0.0f);
            m_EnemyPool->AddNewObjectToPool(Enemy);
            Enemy->SetPool(m_EnemyPool);
        }

        //Lights
        {
            //Old mesh: m_pResources->GetMesh("Plane")
            //Old Mat: m_pResources->GetMaterial("Color")
            Light* light = new Light(this, "Light", vec3(4.0f, 0.0f, 4.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.1f, 0.1f, 0.1f), nullptr, nullptr);
            AddGameObject(light);
            light = new Light(this, "Light2", vec3(-4.0f, 0.0f, -4.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.1f, 0.1f, 0.1f), nullptr, nullptr);
            AddGameObject(light);
            light = new Light(this, "Light3", vec3(-4.0f, 0.0f, 4.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.1f, 0.1f, 0.1f), nullptr, nullptr);
            AddGameObject(light);
            light = new Light(this, "Light4", vec3(4.0f, 0.0f, -4.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.1f, 0.1f, 0.1f), nullptr, nullptr);
            AddGameObject(light);
        }
    }
}

bool MainGameScene::OnEvent(Event* pEvent)
{
    //Pause/Unpause
    if (pEvent->GetEventType() == EventType_Input)
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard)
        {
            int keyID = pInput->GetID();

            if (pInput->GetInputState() == InputState_Pressed)
            {
                if (keyID == 'P')
                {
                    m_pGame->GetSceneManager()->PushScene("PauseMenu");
                }
            }
        }
#endif
    }

    return Scene::OnEvent( pEvent );
}

void MainGameScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    if (m_EnemySpawnTimer <=0.0f)
    {
        if ((MAX_ENEMIES_IN_POOL - m_EnemyPool->GetNumOfObjects())<MAX_ENEMIES)
        {
            SpawnEnemy();
            m_EnemySpawnTimer = ENEMY_SPAWN_DELAY;
        }
    }
    else
    {
        m_EnemySpawnTimer -= deltaTime;
    }
}

void MainGameScene::Draw()
{
    Scene::Draw();
}

void MainGameScene::SetDificulty(DificultyEnum a_Dificulty)
{
    m_Dificulty = a_Dificulty;
    switch (m_Dificulty)
    {
    case DE_Easy:
    {
        MAX_ENEMIES = 3;
        ENEMY_SPAWN_DELAY = 3.0f;

        break;
    }
    case DE_Medium:
    {
        MAX_ENEMIES = 5;
        ENEMY_SPAWN_DELAY = 2.0f;
        break;
    }
    case DE_Hard:
    {
        MAX_ENEMIES = 8;
        ENEMY_SPAWN_DELAY = 1.0f;
        break;
    }
    case DE_WelpBetterGiveUp:
    {
        MAX_ENEMIES = 10;
        ENEMY_SPAWN_DELAY = 0.5f;
        break;
    }
    }
}

void MainGameScene::SpawnBullet(vec3 pos, vec3 rot, float distance, vec4 color)
{
    BulletObject* bullet = static_cast<BulletObject*>(m_BulletPool->GetObjectFromPool());
    if (bullet)
    {
        bullet->SetPosition(pos);
        //vec3 temp = vec3(rot.z, rot.y, -rot.x); //uhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh, it works? *~*
        bullet->SetRotation(rot);
        bullet->SetScale(vec3(0.01f, 0.01f, distance));
        bullet->SetColor(color);

        AddGameObject(bullet);
    }
}

void MainGameScene::SpawnEnemy()
{
    GameObject* enemy = m_EnemyPool->GetObjectFromPool();
    if (enemy)
    {
        //Random position arround the arena
        vec3 heightVariance = vec3(0.0f, 2.0f + ((rand() % 400) / 100.0f - 2.0f), 0.0f);
        vec3 spawnPos = (vec3((float)(rand() % 100 - 50), 0.0f, (float)(rand() % 100 - 50)).Normalize())*ENEMY_SPAWN_DISTANCE + heightVariance;
        enemy->SetPosition(spawnPos);
        //Rotation facing the center of the world
        //spawnPos = GetGameObjectByName("Player")->GetPosition() - spawnPos;
        spawnPos = spawnPos.Normalize();
        float rotX = asin(spawnPos.y);
        float rotY = asin(spawnPos.z / cos(rotX)) * 180 / PI + 180;
        rotX = rotX * 180 / PI;
        vec3 spawnRotation(rotX, rotY, 0.0f);
        //enemy->SetRotation(spawnRotation);
        AddGameObject(enemy);
    }
}

#include "GamePCH.h"

#include "HudScene.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/FollowCamera.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "Physics3D/PhysicsManager.h"
#include "GameObjects/LightObject.h"
#include "GameObjects/HortoCameraObject.h"
#include "GameObjects/UIObject.h"
#include "UI/UIHealthBar.h"

HudScene::HudScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
: Scene(a_Name, pGame, pResources, pPlayer )
{
}

HudScene::~HudScene()
{
}

void HudScene::LoadContent()
{
    Scene::LoadContent();

    //This scene sould probbaly be composed by hud ements
    HortoCameraObject* camera = new HortoCameraObject(this, "Camera", vec3(0.0f, 0.0f, -1.0f), vec3(0.0f), vec3(1.0f));
    AddGameObject(camera);

    UIHealthBar* health = new UIHealthBar(this, "Health", vec3(-5.45f,  2.6f, -1.0f), vec3(0.0f), vec3(1.72f, 1.64f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Health"));
    AddGameObject(health);

    UIObject* aim = new UIObject(this, "Aim", vec3(0.0f, 0.0f, -1.0f), vec3(0.0f), vec3(0.36f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Aim"));
    AddGameObject(aim);
}

bool HudScene::OnEvent(Event* pEvent)
{
    return Scene::OnEvent( pEvent );
}

void HudScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );
}

void HudScene::Draw()
{
    Scene::Draw();
}

#include "GamePCH.h"

#include "OptionsMenuScene.h"
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
#include "UI/BackButton.h"
#include "UI/DificultyButton.h"
#include "GameObjects/UIObject.h"
#include "MainGameScene.h"

OptionsMenuScene::OptionsMenuScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
: Scene(a_Name, pGame, pResources, pPlayer )
{
}

OptionsMenuScene::~OptionsMenuScene()
{
}

void OptionsMenuScene::LoadContent()
{
    Scene::LoadContent();

    //This scene would be composed only of ui elements
    UIObject* bg = new UIObject(this, "BG", vec3(0.0f), vec3(0.0f), vec3(12.8f, 7.2f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("FullBG"));
    AddGameObject(bg);

    HortoCameraObject* camera = new HortoCameraObject(this, "Camera", vec3(0.0f, 0.0f, -1.0f), vec3(0.0f), vec3(1.0f));
    AddGameObject(camera);

    //This scene would be composed only of UI elements
    DificultyButton* dificultyButton = new DificultyButton(DificultyEnum::DE_Easy, this, "EasyButton", vec3(0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("EasyButton"));
    AddGameObject(dificultyButton);

    dificultyButton = new DificultyButton(DificultyEnum::DE_Medium, this, "MediumButton", vec3(0.0f, -0.5f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("MediumButton"));
    AddGameObject(dificultyButton);

    dificultyButton = new DificultyButton(DificultyEnum::DE_Hard, this, "HardButton", vec3(0.0f, -1.0f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("HardButton"));
    AddGameObject(dificultyButton);

    dificultyButton = new DificultyButton(DificultyEnum::DE_WelpBetterGiveUp, this, "WelpButton", vec3(0.0f, -1.5f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("WelpButton"));
    AddGameObject(dificultyButton);

    BackButton* backButton = new BackButton(this, "BackButton", vec3(0.0f, -2.0f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("BackButton"));
    AddGameObject(backButton);
}

bool OptionsMenuScene::OnEvent(Event* pEvent)
{
    return Scene::OnEvent( pEvent );
}

void OptionsMenuScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );
}

void OptionsMenuScene::Draw()
{
    Scene::Draw();
}

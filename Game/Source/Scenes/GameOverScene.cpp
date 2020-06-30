#include "GamePCH.h"

#include "GameOverScene.h"
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
#include "UI/SwitchScreenButton.h"
#include "UI/PopToSceneButton.h"
#include "UI/RestartGameButton.h"
#include "UI/BackButton.h"
#include "GameObjects/UIObject.h"

GameOverScene::GameOverScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
: Scene( a_Name, pGame, pResources, pPlayer )
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::LoadContent()
{
    Scene::LoadContent();
    //This scene would be composed only of ui elements
    UIObject* bg = new UIObject(this, "BG", vec3(0.0f), vec3(0.0f), vec3(12.8f, 7.2f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("FullBG"));
    AddGameObject(bg);

    HortoCameraObject* camera = new HortoCameraObject(this, "Camera", vec3(0.0f, 0.0f, -1.0f), vec3(0.0f), vec3(1.0f));
    AddGameObject(camera);

    SwitchSceneButton* optionsButton = new SwitchSceneButton("OptionsMenuScene", this, "OptionsButton", vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("OptionsButton"));
    AddGameObject(optionsButton);
    RestartGameButton* restartButton = new RestartGameButton(this, "RestartButton", vec3(0.0f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("RestartGameButton"));
    AddGameObject(restartButton);
    PopToSceneButton* mainMenuButton = new PopToSceneButton("TitleScene", this, "QuitToMainMenuButton", vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("QuitToMainMenuButton"));
    AddGameObject(mainMenuButton);
}

bool GameOverScene::OnEvent(Event* pEvent)
{
    return Scene::OnEvent( pEvent );
}

void GameOverScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );
}

void GameOverScene::Draw()
{
    Scene::Draw();
}

#include "GamePCH.h"

#include "TitleScene.h"
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
#include "UI/ExitButton.h"
#include "GameObjects/UIObject.h"

TitleScene::TitleScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
: Scene(a_Name, pGame, pResources, pPlayer )
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::LoadContent()
{
    Scene::LoadContent();

    HortoCameraObject* camera = new HortoCameraObject(this,"Camera", vec3(0.0f,0.0f,-1.0f), vec3(0.0f), vec3(1.0f));
    AddGameObject(camera);

    //This scene would be composed only of UI elements
    UIObject* bg = new UIObject(this, "BG", vec3(0.0f), vec3(0.0f), vec3(12.8f, 7.2f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("FullBG"));
    AddGameObject(bg);

    SwitchSceneButton* startButton = new SwitchSceneButton("MainGameScene", this, "StartButton", vec3(0.0f), vec3(0.0f), vec3(2.56f,0.4f,1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("StartGameButton"));
    AddGameObject(startButton);

    SwitchSceneButton* optionsButton = new SwitchSceneButton("OptionsMenuScene", this, "OptionsButton", vec3(0.0f, -0.5f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("OptionsButton"));
    AddGameObject(optionsButton);

    ExitButton* exitButton = new ExitButton(this, "ExitButton", vec3(0.0f, -1.0f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("ExitGameButton"));
    AddGameObject(exitButton);
}

bool TitleScene::OnEvent(Event* pEvent)
{
    return Scene::OnEvent( pEvent );
}

void TitleScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );
}

void TitleScene::Draw()
{
    Scene::Draw();
}

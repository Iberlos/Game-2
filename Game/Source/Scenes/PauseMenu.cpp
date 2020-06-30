#include "GamePCH.h"

#include "PauseMenu.h"
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
#include "UI/RestartGameButton.h"
#include "UI/BackButton.h"
#include "GameObjects/UIObject.h"

PauseMenu::PauseMenu(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
: Scene(a_Name, pGame, pResources, pPlayer )
{
    m_bCanUnPause = false;
    m_IsOpaque = false;
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::LoadContent()
{
    Scene::LoadContent();

    //This scene would be composed only of UI elements
    HortoCameraObject* camera = new HortoCameraObject(this, "Camera", vec3(0.0f, 0.0f, -1.0f), vec3(0.0f), vec3(1.0f));
    AddGameObject(camera);

    //This scene would be composed only of UI elements
    UIObject* bg = new UIObject(this, "BG", vec3(0.0f), vec3(0.0f), vec3(5.12f, 5.12f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("OverlayBG"));
    AddGameObject(bg);

    SwitchSceneButton* optionsButton = new SwitchSceneButton("OptionsMenuScene", this, "OptionsButton", vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("OptionsButton"));
    AddGameObject(optionsButton);

    RestartGameButton* restartButton = new RestartGameButton(this, "RestartButton", vec3(0.0f, -0.5f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("RestartGameButton"));
    AddGameObject(restartButton);

    SwitchSceneButton* mainMenuButton = new SwitchSceneButton("TitleScene", this, "QuitToMainMenuButton", vec3(0.0f, -1.0f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("QuitToMainMenuButton"));
    AddGameObject(mainMenuButton);

    BackButton* backButton = new BackButton(this, "BackButton", vec3(0.0f, -1.5f, 0.0f), vec3(0.0f), vec3(2.56f, 0.4f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("BackButton"));
    AddGameObject(backButton);
}

bool PauseMenu::OnEvent(Event* pEvent)
{
    Scene::OnEvent( pEvent );

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
                    if (m_bCanUnPause)
                    {
                        //remove ourselves from the scene manager
                        //m_pGame->GetSceneManager()->PopScene();
                        m_bCanUnPause = false;
                    }
                }
            }
            else if (pInput->GetInputState() == InputState_Released)
            {
                if (keyID == 'P')
                {
                    m_bCanUnPause = true;
                }
            }
        }
#endif
    }

    return true;
}

void PauseMenu::Update(float deltaTime)
{
    Scene::Update( deltaTime );
}

void PauseMenu::Draw()
{
    Scene::Draw();
}

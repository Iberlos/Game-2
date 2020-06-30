#include "GamePCH.h"

#include "SceneSample.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/SceneManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/FollowCamera.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "Physics3D/PhysicsManager.h"
#include "GameObjects/LightObject.h"
#include "FBOs/FBODefinition.h"
#include "UI/SwitchScreenButton.h"

SceneSample::SceneSample(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
: Scene(a_Name, pGame, pResources, pPlayer )
{
    m_Hinge = nullptr;
}

SceneSample::~SceneSample()
{
    delete m_Hinge;
}

void SceneSample::LoadContent()
{
    Scene::LoadContent();
}

bool SceneSample::OnEvent(Event* pEvent)
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
                    //ShowCursor(true);
                }
            }
        }
#endif
    }

    return Scene::OnEvent(pEvent);
}

void SceneSample::Update(float deltaTime)
{
    Scene::Update( deltaTime );
}

void SceneSample::Draw()
{
    Scene::Draw();
}

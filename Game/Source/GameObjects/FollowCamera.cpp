#include "GamePCH.h"

#include "FollowCamera.h"
#include "Game/Game.h"
#include "Game/Scene.h"
//To recognize the const in player, possibly should be adjusted
#include "GameObjects/Player.h"

FollowCamera::FollowCamera(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, float a_followDistance, GameObject* a_target): CameraObject(pScene, name, pos, rot, scale),
m_followDistance(a_followDistance),
m_target(a_target),
m_LastMousePosition(0,0)
{
    m_DebugDraw = true;
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update(float deltaTime)
{
    if (m_Rotation.x <= -89.9f)
    {
        m_Rotation.x = -89.9f;
    }
    if (m_Rotation.x > 89.9f)
    {
        m_Rotation.x = 89.9f;
    }
    m_Rotation.y = m_target->GetRotation().y;

    GameObject::Update(deltaTime);

    SetPosition(m_target->GetPosition() - vec3(m_ForwardVector)*m_followDistance);
    m_LookAtPosition = m_target->GetPosition();

    // Setup camera/view matrix.
    m_ViewMatrix.CreateLookAtView(m_Position, vec3(0, 1, 0), m_LookAtPosition);

    float windowWidth = (float)m_pScene->GetGame()->GetFramework()->GetWindowWidth();
    float windowHeight = (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight();
    m_ProjMatrix.CreatePerspectiveVFoV(45, windowWidth / windowHeight, 0.01f, 1000.0f);
}

void FollowCamera::OnEvent(Event* pEvent)
{
    if (pEvent->GetEventType() == EventType_Input)
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);
        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse)
        {
            if (pInput->GetInputState() == InputState_Held)
            {
                int screenMidX = static_cast<int>(m_pScene->GetGame()->GetFramework()->GetWindowWidth() * 0.5f);
                int screenMidY = static_cast<int>(m_pScene->GetGame()->GetFramework()->GetWindowHeight() * 0.5f);

                float mouseDifY = pInput->GetPosition().y - (float)screenMidY;
                //OutputMessage("Mouse Event Pos x: %f, y: %f \n", pInput->GetPosition().x, pInput->GetPosition().y);
                m_Rotation.x -= mouseDifY * MOUSE_ROT_SPEED;
                m_LastMousePosition = pInput->GetPosition();

                //Resetting the mouse position every frame
                m_pScene->GetGame()->GetFramework()->SetMousePosition(ivec2(screenMidX, screenMidY));
            }
        }
#endif
    }
}

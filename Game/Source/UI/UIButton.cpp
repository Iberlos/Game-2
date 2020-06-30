#include "GamePCH.h"
#include "UIButton.h"
#include "../GameObjects/UIObject.h"
#include "Game/Scene.h"
#include "Game/Game.h"
#include "../Mesh/Mesh.h"
#include "../Game/ResourceManager.h"
#include "../Audio/SoundPlayer.h"

UIButton::UIButton(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial): UIObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_StateColor = vec4(1,1,1,1);
}

UIButton::~UIButton()
{
}

void UIButton::OnEvent(Event * pEvent)
{
    if (pEvent->GetEventType() == EventType_Input)
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);
        if (pInput->GetInputState() == InputState_Held)
        {
            if (IsMouseOnButton(pInput->GetPosition())&&m_State!=EBS_Clicked)
            {
                m_State = EBS_Hovered;
            }
            if (!IsMouseOnButton(pInput->GetPosition()))
            {
                m_State = EBS_Idle;
            }
        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse)
        {
            int buttonID = pInput->GetID();
            if (pInput->GetInputState() == InputState_Pressed)
            {
                if (IsMouseOnButton(pInput->GetPosition()))
                {
                    m_State = EBS_Clicked;
                }
            }
            else if (pInput->GetInputState() == InputState_Released)
            {
                if (IsMouseOnButton(pInput->GetPosition()))
                {
                    Execute();
                }
            }
        }
#endif
    }
}

void UIButton::Update(float deltaTime)
{
    switch (m_State)
    {
    case EBS_Hovered:
    {
        if (m_StateColor != vec4(1.0f, 0.0f, 0.0f, 1.0f))
        {
            m_StateColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
        }
        break;
    }
    case EBS_Clicked:
    {
        if (m_StateColor != vec4(1.0f, 1.0f, 0.0f, 1.0f))
        {
            m_StateColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
            m_pScene->GetSoundPlayer()->PlaySound(m_pScene->GetResourceManager()->GetSound("ButtonResponseClick"));
        }
        break;
    }
    default:
    {
        if (m_StateColor != vec4(1.0f, 1.0f, 1.0f, 1.0f))
        {
            m_StateColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
        break;
    }
    }
}

void UIButton::Execute()
{
    m_pScene->GetSoundPlayer()->PlaySound(m_pScene->GetResourceManager()->GetSound("ButtonResponseConfirm"));
}

bool UIButton::IsMouseOnButton(vec2 a_position)
{
    float windowWidth = (float)m_pScene->GetGame()->GetFramework()->GetWindowWidth();
    float windowHeight = (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight();
    a_position -= vec2(windowWidth*0.5f, windowHeight*0.5f); //offset for origin
    a_position.y *= -1;
    a_position /= 100; //world to pixels ratio

    if (a_position.x > (m_Position.x - m_Scale.x / 2) && a_position.x<(m_Position.x + m_Scale.x / 2) && a_position.y>(m_Position.y - m_Scale.y / 2) && a_position.y < (m_Position.y + m_Scale.y / 2))
    {
        return true;
    }
    return false;
}

void UIButton::SetupUniforms()
{
    SetUniform4f(m_pMaterial->GetShader()->GetProgram(), "u_Color", m_StateColor);
}

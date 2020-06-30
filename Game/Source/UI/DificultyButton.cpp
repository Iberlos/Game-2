#include "GamePCH.h"
#include "DificultyButton.h"
#include "../Game/Scene.h"
#include "../Game/Game.h"
#include "../Game/SceneManager.h"
#include "../Scenes/MainGameScene.h"
#include "../Game/ResourceManager.h"
#include "../Audio/SoundPlayer.h"

DificultyButton::DificultyButton(DificultyEnum a_Dificulty, Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial):UIButton(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_GameScene = dynamic_cast<MainGameScene*>(m_pScene->GetGame()->GetSceneManager()->GetScene("MainGameScene"));
    m_Dificulty = a_Dificulty;
}

DificultyButton::~DificultyButton()
{
}

void DificultyButton::Update(float deltaTime)
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
        if (m_StateColor != vec4(1.0f, 1.0f, 0.0f, 1.0f) && m_StateColor != vec4(0.0f, 1.0f, 0.0f, 1.0f))
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
    if (m_GameScene->GetDificulty() == m_Dificulty)
    {
        m_StateColor = vec4(0.0f,1.0f,0.0f,1.0f);
    }
}

void DificultyButton::Execute()
{
    UIButton::Execute();
    m_GameScene->SetDificulty(m_Dificulty);
}

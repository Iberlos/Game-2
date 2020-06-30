#include "GamePCH.h"
#include "SwitchScreenButton.h"
#include "../Game/Scene.h"
#include "../Game/Game.h"
#include "../Game/SceneManager.h"

SwitchSceneButton::SwitchSceneButton(std::string a_LinkedScene, Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial): UIButton(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_LinkedScene = a_LinkedScene;
}

SwitchSceneButton::~SwitchSceneButton()
{
}

void SwitchSceneButton::Execute()
{
    UIButton::Execute();
    m_pScene->GetGame()->GetSceneManager()->PushScene(m_LinkedScene);
}

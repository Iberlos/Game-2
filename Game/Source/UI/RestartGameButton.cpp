#include "GamePCH.h"
#include "RestartGameButton.h"
#include "../Game/Scene.h"
#include "../Game/Game.h"
#include "../Game/SceneManager.h"

RestartGameButton::RestartGameButton(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial) :UIButton(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
}

RestartGameButton::~RestartGameButton()
{
}

void RestartGameButton::Execute()
{
    UIButton::Execute();
    m_pScene->GetGame()->GetSceneManager()->GetScene("MainGameScene")->Reset();
    m_pScene->GetGame()->GetSceneManager()->PopToScene("MainGameScene");
}

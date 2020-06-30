#include "GamePCH.h"
#include "BackButton.h"
#include "../Game/Scene.h"
#include "../Game/Game.h"
#include "../Game/SceneManager.h"

BackButton::BackButton(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial):UIButton(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
}

BackButton::~BackButton()
{
}

void BackButton::Execute()
{
    UIButton::Execute();
    m_pScene->GetGame()->GetSceneManager()->PopScene();
}

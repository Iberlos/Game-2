#include "GamePCH.h"
#include "PopToSceneButton.h"
#include "../Game/Scene.h"
#include "../Game/Game.h"
#include "../Game/SceneManager.h"

PopToSceneButton::PopToSceneButton(std::string a_LinkedScene, Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial) : UIButton(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_LinkedScene = a_LinkedScene;
}

PopToSceneButton::~PopToSceneButton()
{
}

void PopToSceneButton::Execute()
{
    UIButton::Execute();
    m_pScene->GetGame()->GetSceneManager()->PopToScene(m_LinkedScene);
}

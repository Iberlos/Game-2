#include "GamePCH.h"
#include "ExitButton.h"
#include "../Game/Scene.h"
#include "../Game/Game.h"
#include "../Game/SceneManager.h"

ExitButton::ExitButton(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial):UIButton(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
}

ExitButton::~ExitButton()
{
}

void ExitButton::Execute()
{
    //UIButton::Execute();
    m_pScene->GetGame()->GetFramework()->SetCloseProgramRequested(true);
}

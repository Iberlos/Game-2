#include "GamePCH.h"
#include "UIHealthBar.h"
#include "Mesh/Mesh.h"
#include "Mesh/Material.h"
#include "Game/Scene.h"
#include "Game/Game.h"
#include "Game/SceneManager.h"
#include "GameObjects/Player.h"

UIHealthBar::UIHealthBar(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial) : UIObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_Player = dynamic_cast<Player*>(m_pScene->GetGame()->GetSceneManager()->GetScene("MainGameScene")->GetGameObjectByName("Player"));
}

UIHealthBar::~UIHealthBar()
{
}

void UIHealthBar::SetupUniforms()
{
    SetUniform4f(m_pMaterial->GetShader()->GetProgram(), "u_ColorMask", vec4(1.0f, 1.0f, 1.0f, 1.0f));
    SetUniform4f(m_pMaterial->GetShader()->GetProgram(), "u_Color", vec4(1.0f, 0.0f, 0.0f, 1.0f));
    SetUniform1f(m_pMaterial->GetShader()->GetProgram(), "u_Percent", m_Player->GetHealthPercent());
}

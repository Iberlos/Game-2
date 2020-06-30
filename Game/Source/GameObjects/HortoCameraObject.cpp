#include "GamePCH.h"

#include "HortoCameraObject.h"
#include "Game/Game.h"
#include "Game/Scene.h"

HortoCameraObject::HortoCameraObject(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale): 
    CameraObject(pScene, name, pos, rot, scale)
{
    m_LookAtPosition = m_Position + vec3(0, 0, 1);

    // Setup camera/view matrix.
    m_ViewMatrix.CreateLookAtView(m_Position, vec3(0, 1, 0), m_LookAtPosition);
    float windowWidth = (float)m_pScene->GetGame()->GetFramework()->GetWindowWidth();
    float windowHeight = (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight();
    m_ProjMatrix.CreateOrtho(-windowWidth*0.005f, windowWidth*0.005f, -windowHeight*0.005f, windowHeight*0.005f, 0, 100);
}

HortoCameraObject::~HortoCameraObject()
{
}

void HortoCameraObject::Update(float deltaTime)
{
    GameObject::Update(deltaTime);
}

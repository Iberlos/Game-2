#include "GamePCH.h"

#include "CameraObject.h"
#include "Game/Game.h"
#include "Game/Scene.h"

CameraObject::CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
: GameObject( pScene, name, pos, rot, scale, 0, 0 )
{
    m_LookAtPosition = m_Position + vec3(0.0f, 0.0f, 15.0f);
}

CameraObject::~CameraObject()
{
}

void CameraObject::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    // Setup camera/view matrix.
    m_ViewMatrix.CreateLookAtView( m_Position, vec3(0,1,0), m_LookAtPosition );

    float windowWidth = (float)m_pScene->GetGame()->GetFramework()->GetWindowWidth();
    float windowHeight = (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight();
    m_ProjMatrix.CreatePerspectiveVFoV( 45, windowWidth/windowHeight, 0.01f, 1000.0f );
}

#include "GamePCH.h"
#include "UIObject.h"
#include "Mesh/Material.h"
#include "Game/Scene.h"
#include "GameObjects/CameraObject.h"
#include "Mesh/Mesh.h"
#include "Game/Scene.h"
#include "Game/SceneManager.h"

UIObject::UIObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial) : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    //This class would hold the colde for snapping to positions on the screen while the subclasses would hold more specific code related to their functionality

    m_Tags.push_back("UIObject");
}

UIObject::~UIObject()
{
}

void UIObject::Draw(CameraObject* pCamera)
{
    GameObject::Draw(pCamera);
}
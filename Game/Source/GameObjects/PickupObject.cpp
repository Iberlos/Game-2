#include "GamePCH.h"
#include "PickupObject.h"

PickupObject::PickupObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    //nada
}

PickupObject::~PickupObject()
{

}

void PickupObject::OnContactStarted(GameObject* otherObject, vec3 worldNormal)
{
    //If the player hits us
    if (otherObject->ObjectHasTag("Player"))
    {
        RandomDrop();
    }
}

void PickupObject::RandomDrop()
{
    vec3 centerpoint = vec3(-5.0f, 2.0f, 2.5f);
    //Generate numbers between -5 and +5 for x and z
    int xChange = rand() % 9 - 4;
    int zChange = rand() % 9 - 4;

    centerpoint += vec3((float)xChange, 0.0f, (float)zChange);

    m_Body->activate(true);
    SetPosition(centerpoint);
}

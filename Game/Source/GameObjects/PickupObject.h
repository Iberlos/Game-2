#pragma once

#include "GameObject.h"

class PickupObject : public GameObject
{
public:
    PickupObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    ~PickupObject();
public:
    virtual void OnContactStarted(GameObject* otherObject, vec3 worldNormal) override;
    void RandomDrop();

};
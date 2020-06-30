#pragma once
#include "GameObject.h"


class UIObject : public GameObject
{
public:
    UIObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~UIObject();


    virtual void Draw(CameraObject* pCamera) override;

};

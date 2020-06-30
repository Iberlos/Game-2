#pragma once
#include "UIButton.h"

class BackButton : public UIButton
{
public:
    BackButton(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~BackButton();
protected:
    virtual void Execute() override;
};
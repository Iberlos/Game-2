#pragma once
#include "UIButton.h"

class ExitButton : public UIButton
{
public:
    ExitButton(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~ExitButton();
protected:
    virtual void Execute() override;
};
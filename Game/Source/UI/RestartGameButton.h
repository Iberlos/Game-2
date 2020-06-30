#pragma once
#include "UIButton.h"

class RestartGameButton : public UIButton
{
public:
    RestartGameButton(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~RestartGameButton();
protected:
    virtual void Execute() override;
};
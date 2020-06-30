#pragma once
#include "UIButton.h"
#include <string>

class SwitchSceneButton : public UIButton
{
public:
    SwitchSceneButton(std::string a_LinkedScene, Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~SwitchSceneButton();

    virtual void Execute() override;
protected:
    std::string m_LinkedScene;
};
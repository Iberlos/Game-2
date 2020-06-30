#pragma once
#include "UIButton.h"
#include <string>

class PopToSceneButton : public UIButton
{
public:
    PopToSceneButton(std::string a_LinkedScene, Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~PopToSceneButton();

    virtual void Execute() override;
protected:
    std::string m_LinkedScene;
};
#pragma once
#include "GameObjects/UIObject.h"

class Player;

class UIHealthBar : public UIObject
{
public:
    UIHealthBar(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~UIHealthBar();
protected:
    virtual void SetupUniforms() override;
    Player* m_Player;
};

#pragma once
#include "UIButton.h"

enum DificultyEnum;
class MainGameScene;

class DificultyButton : public UIButton
{
public:
    DificultyButton(DificultyEnum a_dificulty, Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~DificultyButton();
    virtual void Update(float deltaTime) override;
protected:
    virtual void Execute() override;
    DificultyEnum m_Dificulty;
    MainGameScene* m_GameScene;
};
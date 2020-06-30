#pragma once
#include "GameObjects/UIObject.h"

class CameraObject;

enum ButtonStates
{
    EBS_Idle = 0,
    EBS_Hovered,
    EBS_Clicked
};

class UIButton : public UIObject
{
public:
    UIButton(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~UIButton();

    virtual void OnEvent(Event* a_Event) override;

    virtual void Update(float deltaTime) override;

    virtual void Execute();

    bool IsMouseOnButton(vec2 a_position);
protected:
    vec4 m_StateColor;
    ButtonStates m_State;

    virtual void SetupUniforms() override;
};
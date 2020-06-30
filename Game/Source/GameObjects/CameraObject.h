#ifndef __CameraObject_H__
#define __CameraObject_H__

#include "GameObject.h"

class CameraObject : public GameObject
{
protected:
    mat4 m_ViewMatrix;
    mat4 m_ProjMatrix;
    vec3 m_LookAtPosition;

public:
    CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~CameraObject();

    virtual void Update(float deltaTime) override;

    mat4* GetViewMatrix() { return &m_ViewMatrix; }
    mat4* GetProjMatrix() { return &m_ProjMatrix; }
    void SetLookAtPosition(vec3 pos) { m_LookAtPosition = pos; }
};

#endif //__CameraObject_H__

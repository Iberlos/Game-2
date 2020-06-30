#ifndef __HortoCameraObject_H__
#define __HortoCameraObject_H__

#include "CameraObject.h"

class HortoCameraObject : public CameraObject
{

public:
    HortoCameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~HortoCameraObject();

    virtual void Update(float deltaTime) override;
};

#endif //__CameraObject_H__

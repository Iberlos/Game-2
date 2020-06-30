#ifndef __SceneSample_H__
#define __SceneSample_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;

class SceneSample : public Scene
{
protected:
    btHingeConstraint * m_Hinge;

public:
    SceneSample(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    virtual ~SceneSample();

    virtual void LoadContent() override;

    virtual bool OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__SceneSample_H__

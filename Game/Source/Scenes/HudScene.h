#ifndef __HudScene_H__
#define __HudScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;

class HudScene : public Scene
{
protected:

public:
    HudScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    virtual ~HudScene();

    virtual void LoadContent() override;

    virtual bool OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__HudScene_H__

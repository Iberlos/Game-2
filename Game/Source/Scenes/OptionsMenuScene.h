#ifndef __OptionsMenuScene_H__
#define __OptionsMenuScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;

class OptionsMenuScene : public Scene
{
protected:

public:
    OptionsMenuScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    virtual ~OptionsMenuScene();

    //virtual void OnFocusOn() override { ShowCursor(true); }

    virtual void LoadContent() override;

    virtual bool OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__OptionsMenuScene_H__

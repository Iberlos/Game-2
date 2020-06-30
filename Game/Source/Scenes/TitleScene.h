#ifndef __TitleScene_H__
#define __TitleScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;

class TitleScene : public Scene
{
protected:

public:
    TitleScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    virtual ~TitleScene();

    //virtual void OnFocusOn() override { ShowCursor(true); }

    virtual void LoadContent() override;

    virtual bool OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__TitleScene_H__

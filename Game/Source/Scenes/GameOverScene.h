#ifndef __GameOverScene_H__
#define __GameOverScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;

class GameOverScene : public Scene
{
protected:

public:
    GameOverScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    virtual ~GameOverScene();

    virtual void OnFocusOn() override { ShowCursor(true); }

    virtual void LoadContent() override;

    virtual bool OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__GameOverScene_H__

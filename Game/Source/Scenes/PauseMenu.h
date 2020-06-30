#ifndef __PauseMenu_H__
#define __PauseMenu_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;

class PauseMenu : public Scene
{
protected:

public:
    PauseMenu(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    virtual ~PauseMenu();

    virtual void OnFocusOn() override { ShowCursor(true); }

    virtual void LoadContent() override;

    virtual bool OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

protected:
    bool m_bCanUnPause;
};

#endif //__PauseMenu_H__

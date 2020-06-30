#pragma once

#include "Game/Scene.h"

class GunScene : public Scene
{
public:
    GunScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    ~GunScene();


    virtual void LoadContent() override;


    virtual void Draw() override;

protected:
};
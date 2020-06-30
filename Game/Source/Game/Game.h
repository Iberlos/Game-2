#ifndef __Game_H__
#define __Game_H__

class ImGuiManager;
class ResourceManager;
class Texture;
class SceneManager;
class Mesh;
class GameObject;
class Player;
class PlayerController;
class SoundPlayer;
class FBODefinition;

class Game : public GameCore
{
protected:
    ImGuiManager* m_pImGuiManager;
    bool m_bDrawImGui;

    ResourceManager* m_pResources;

    SoundPlayer* m_SoundPlayer;

    SceneManager* m_pSceneManager;

    PlayerController* m_pControllers[4];

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height) override;
    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    PlayerController* GetController(int index) { return m_pControllers[index]; }
    SceneManager* GetSceneManager() { return m_pSceneManager;  }
    bool GetDebugDraw() { return m_bDrawImGui; }
};

#endif //__Game_H__

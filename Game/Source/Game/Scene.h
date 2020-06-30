#ifndef __Scene_H__
#define __Scene_H__

class Game;
class GameObject;
class ResourceManager;
class PhysicsManager;
class SoundPlayer;
class Light;
class FBODefinition;
class ShaderProgram;

class Scene
{
private:
    std::vector<GameObject*> m_pGameObjects;

    bool m_Paused;
protected:
    std::string m_Name;
    Game* m_pGame;
    ResourceManager* m_pResources;
    SoundPlayer* m_SoundPlayer;

    PhysicsManager* m_PhysicsManager;

    FBODefinition* m_FBO;

    ShaderProgram* m_PostEffectShader;

    std::vector<Scene*> m_SubScenes;

    bool m_IsOpaque;
public:
    Scene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    virtual ~Scene();

    void Cleanup();

    virtual void OnFocusOn() {}
    virtual void OnFocusOff() {}
    virtual void OnScenePopped() {}

    virtual void LoadContent();

    virtual void Reset();

    virtual bool OnEvent(Event* pEvent);
    virtual void Update(float deltaTime);
    virtual void Draw();

    void AddGameObject(GameObject* pObject);
    bool RemoveGameObject(GameObject* pObject);
    void AddSubScene(Scene* subScene);
    bool IsGameObjectInScene(GameObject* pObject);

    GameObject* GetGameObjectByName(std::string name);
    std::string GetName() { return m_Name; }
    bool GetIsOpaque() { return m_IsOpaque; }
    Game* GetGame() { return m_pGame; }
    ResourceManager* GetResourceManager() { return m_pResources; }
    std::vector<Light*> GetLights();
    bool GetDebugDraw();

    //Physics
    PhysicsManager* GetPhysicsManager() { return m_PhysicsManager; }

    //Sound
    SoundPlayer* GetSoundPlayer() { return m_SoundPlayer; }

    //Posteffect
    void SetPostEffectShader(ShaderProgram* a_shader) { m_PostEffectShader = a_shader; }
};

#endif //__Scene_H__

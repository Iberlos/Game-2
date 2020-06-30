#ifndef __SceneManager_H__
#define __SceneManager_H__

class Scene;
class ResourceManager;

class SceneManager
{
public:
    SceneManager( ResourceManager* a_Resources);
    ~SceneManager();

    void AddNewScene(std::string a_sceneKey, Scene* a_scene);
    Scene* GetScene(std::string sceneName);

    void PushScene(std::string a_sceneKey);
    void PopScene();
    bool PopToScene(std::string a_sceneKey);

    void OnEvent(Event* a_event);
    void Update(float a_DeltaTime);
    void Draw();
    void Reset();
    void CreateImGuiWinow();

protected:
    std::map<std::string, Scene*> m_Scenes;
    std::vector<std::string> m_SceneStack;
    ResourceManager* m_Resources;

    bool m_bDrawDebug;
};

#endif
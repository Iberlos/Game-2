#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Game.h"
#include "ResourceManager.h"

SceneManager::SceneManager(ResourceManager* a_Resources)
{
    m_Resources = a_Resources;
}

SceneManager::~SceneManager()
{
    for (auto object : m_Scenes)
    {
        delete object.second;
    }
}

void SceneManager::AddNewScene(std::string a_sceneKey, Scene * a_scene)
{
    if (m_Scenes.find(a_sceneKey) == m_Scenes.end())
    {
        m_Scenes[a_sceneKey] = a_scene;
    }
    else
    {
        assert(false); //scene already in map
    }
}

Scene* SceneManager::GetScene(std::string sceneName)
{
    auto it = m_Scenes.find(sceneName);
    if (it == m_Scenes.end())
        return nullptr;

    return it->second;
}

void SceneManager::PushScene(std::string a_sceneKey)
{
    assert(m_Scenes.find(a_sceneKey) != m_Scenes.end()); //Scene was not created prior to being pushed.
    if(m_SceneStack.size() != 0)
        m_Scenes[m_SceneStack.back()]->OnFocusOff();
    m_SceneStack.push_back(a_sceneKey);
    m_Scenes[m_SceneStack.back()]->OnFocusOn();
}

void SceneManager::PopScene()
{
    assert(m_SceneStack.size() != 0);//No scenes to pop
    m_Scenes[m_SceneStack.back()]->OnScenePopped();
    m_SceneStack.pop_back();
    m_Scenes[m_SceneStack.back()]->OnFocusOn();
}

bool SceneManager::PopToScene(std::string a_sceneKey)
{
    bool searchResult = false;
    for (unsigned int i = 0; i < m_SceneStack.size(); i++)
    {
        if (m_Scenes[m_SceneStack[i]]->GetName() == a_sceneKey)
        {
            searchResult = true;
            break;
        }
    }
    if (searchResult == true)
    {
        unsigned int count = m_SceneStack.size() - 1;
        while (m_Scenes[m_SceneStack[count]]->GetName() != a_sceneKey)
        {
            PopScene();
            count = m_SceneStack.size() - 1;
            assert(count >= 0);
        }
    }
    else
    {
        assert(false); //The scene was not in the stack, review your logic.
    }
    return searchResult;
}

void SceneManager::OnEvent(Event * a_event)
{
    int topOpaque = 0;
    for (int i = m_SceneStack.size() - 1; i >= 0; i--)
    {
        if (m_Scenes[m_SceneStack.at(i)]->GetIsOpaque())
        {
            topOpaque = i;
            break;
        }
    }

    for (int i = m_SceneStack.size() - 1; i >= topOpaque; i--)
    {
        //if the scene has used up the event
        if (m_Scenes[m_SceneStack[i]]->OnEvent(a_event))
        {
            break;
        }
    }
}

void SceneManager::Update(float a_DeltaTime)
{
    m_Scenes[m_SceneStack.back()]->Update(a_DeltaTime);
}

void SceneManager::Draw()
{
    int topOpaque = 0;
    for (int i = m_SceneStack.size() - 1; i >= 0; i--)
    {
        if (m_Scenes[m_SceneStack.at(i)]->GetIsOpaque())
        {
            topOpaque = i;
            break;
        }
    }

    for (unsigned int i = topOpaque; i < m_SceneStack.size(); i++)
    {
        if (i == m_SceneStack.size() - 1)
            m_Scenes[m_SceneStack[i]]->SetPostEffectShader(nullptr);
        else
            m_Scenes[m_SceneStack[i]]->SetPostEffectShader(m_Resources->GetShader("PostEffectGreyscale"));
        m_Scenes[m_SceneStack[i]]->Draw();
    }
    

    //Grab the debug status from the game using the top scene
    m_bDrawDebug = m_Scenes[m_SceneStack.back()]->GetGame()->GetDebugDraw();
    if (m_bDrawDebug)
        CreateImGuiWinow();
}

void SceneManager::Reset()
{
    //for now just reset the top scene, in the future we would reset the entire game? not sure. 
    m_Scenes[m_SceneStack.back()]->Reset();
}

void SceneManager::CreateImGuiWinow()
{
    ImGui::Begin("SceneManager");
    ImGui::Text("Scenes in Stack:");
    ImGui::Indent();
    for (int i = m_SceneStack.size() - 1; i >= 0; i--)
    {
        ImGui::Text(m_SceneStack[i].c_str());
    }
    ImGui::Unindent();
    ImGui::End();
}

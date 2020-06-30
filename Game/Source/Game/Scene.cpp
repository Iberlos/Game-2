#include "GamePCH.h"

#include "Game.h"
#include "Game/ResourceManager.h"
#include "Game/ObjectPool.h"
#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/LightObject.h"
#include "Physics3D/PhysicsManager.h"
#include "FBOs/FBODefinition.h"

Scene::Scene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
{
    m_Name = a_Name;
    m_pGame = pGame;
    m_pResources = pResources;
    m_SoundPlayer = pPlayer;
    m_Paused = false;
    m_IsOpaque = true;

    m_FBO = nullptr;
}

Scene::~Scene()
{
    Cleanup();
}

void Scene::Cleanup()
{
    for( auto pObject: m_pGameObjects )
    {
        delete pObject;
    }
    m_pGameObjects.clear();

    delete m_PhysicsManager;
    delete m_FBO;
}

void Scene::LoadContent()
{
    //Physics world
    m_PhysicsManager = nullptr;

    //FBOs
    m_FBO = new FBODefinition(m_pGame->GetFramework()->GetWindowWidth(), m_pGame->GetFramework()->GetWindowHeight(), GL_LINEAR, GL_LINEAR, true);

    //Generic scene post effect
    if (!m_pResources->GetShader("PostEffectGreyscale"))
        m_pResources->AddShader("PostEffectGreyscale", new ShaderProgram("Data/Shaders/PostEffectShaders/PostEffect.vert", "Data/Shaders/PostEffectShaders/PostEffectGreyscale.frag"));

    //scene texture
    m_pResources->AddTexture(m_Name, new Texture(m_FBO->GetColorTextureHandle(), 2048, 1024));
    //scene material initially with no post effect
    m_pResources->AddMaterial(m_Name, new Material(m_PostEffectShader, m_pResources->GetTexture(m_Name)));

    //SET THE SCENE POST EFFECT SHADER
    m_PostEffectShader = nullptr;
}

void Scene::Reset()
{
    // Reset all of the Scene objects in the list.
    for( auto pObject: m_pGameObjects )
    {
        pObject->Reset();
    }

    for (auto pScene : m_SubScenes)
    {
        pScene->Reset();
    }
}

bool Scene::OnEvent(Event* pEvent)
{
    //test
    if (pEvent->GetEventType() == EventType_Input)
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard)
        {
            int keyID = pInput->GetID();

            if (pInput->GetInputState() == InputState_Pressed)
            {
                if (keyID == 'I')
                {
                    if (!m_PostEffectShader)
                        m_PostEffectShader = m_pResources->GetShader("PostEffectGreyscale");
                    else
                        m_PostEffectShader = nullptr;
                }
            }
        }
#endif
    }

    // Send the event to Scene objects in the list.
    /*
    for (auto pObject : m_pGameObjects)
    {
        pObject->OnEvent(pEvent);
    }
    /*/
    for ( unsigned int i = 0; i < m_pGameObjects.size(); i++)
    {
        m_pGameObjects.at(i)->OnEvent(pEvent);
    }
    //*/

    for (auto pScene : m_SubScenes)
    {
        pScene->OnEvent(pEvent);
    }
    return false;
}

void Scene::Update(float deltaTime)
{
    CheckForGLErrors();

    // Update all of the Scene objects in the list.
    if (!m_Paused)
    {
        for (unsigned int i = 0; i < m_pGameObjects.size(); i++)
        {
            m_pGameObjects[i]->Update(deltaTime);
        }

        for (auto pScene : m_SubScenes)
        {
            pScene->Update(deltaTime);
        }

        if (m_PhysicsManager)
        {
            m_PhysicsManager->Update(deltaTime);
        }
    }
    CheckForGLErrors();
}

void Scene::Draw()
{
    CheckForGLErrors();
    glClear(GL_DEPTH_BUFFER_BIT);
    CameraObject* pCamera = static_cast<CameraObject*>( GetGameObjectByName( "Camera" ) );
    assert( pCamera );

    if (m_PostEffectShader)
    {
        m_FBO->Bind();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        //Render all of the Scene objects in the list.
        for (auto pObject : m_pGameObjects)
        {
            pObject->Draw(pCamera);
        }

        for (unsigned int i = 0; i < m_SubScenes.size(); i++)
        {
            m_SubScenes[i]->Draw();
        }

        if (m_PhysicsManager)
        {
            m_PhysicsManager->SetImGuiDebugDraw(GetDebugDraw());
            m_PhysicsManager->Draw();
        }

        m_FBO->Unbind();

        //Draw into the canvas
        Material* material = m_pResources->GetMaterial(m_Name);
        material->SetShader(m_PostEffectShader);
        Mesh* mesh = m_pResources->GetMesh("Box");
        mesh->SetupAttributes(material);
        MyMatrix worldMat;
        worldMat.CreateSRT(0, 0, 0);
        MyMatrix rotMat;
        rotMat.CreateRotation(0);
        mesh->SetupUniforms(m_pResources->GetMaterial(m_Name), &worldMat, &rotMat, pCamera, 1, 0, GetLights());
        mesh->Draw(m_pResources->GetMaterial(m_Name));
    }
    else
    {
        for (auto pObject : m_pGameObjects)
        {
            pObject->Draw(pCamera);
        }

        for (auto pScene : m_SubScenes)
        {
            pScene->Draw();
        }

        if (m_PhysicsManager)
        {
            m_PhysicsManager->SetImGuiDebugDraw(GetDebugDraw());
            m_PhysicsManager->Draw();
        }
    }

    CheckForGLErrors();
}

void Scene::AddGameObject(GameObject* pObject)
{
    m_pGameObjects.push_back( pObject );
}

bool Scene::RemoveGameObject(GameObject* pObject)
{
    auto iteratorForObject = std::find( m_pGameObjects.begin(), m_pGameObjects.end(), pObject );
    
    if( iteratorForObject != m_pGameObjects.end() )
    {
        m_pGameObjects.erase( iteratorForObject );
        return true;
    }

    return false;
}

void Scene::AddSubScene(Scene* subScene)
{
    if (subScene)
        m_SubScenes.push_back(subScene);
}

bool Scene::IsGameObjectInScene(GameObject* pObject)
{
    auto iteratorForObject = std::find( m_pGameObjects.begin(), m_pGameObjects.end(), pObject );

    if( iteratorForObject != m_pGameObjects.end() )
    {
        return true;
    }

    return false;
}

GameObject* Scene::GetGameObjectByName(std::string name)
{
    for( auto pObject: m_pGameObjects )
    {
        if( pObject->GetName() == name )
        {
            return pObject;
        }
    }

    return nullptr;
}


std::vector<Light*> Scene::GetLights()
{
    std::vector<Light*> lights;
    for each (GameObject* object in m_pGameObjects)
    {
        if (object->ObjectHasTag("Light"))
        {
            Light* light = static_cast<Light*>(object);
            lights.push_back(light);
        }
    }
    return lights;
}

bool Scene::GetDebugDraw()
{
    return m_pGame->GetDebugDraw();
}

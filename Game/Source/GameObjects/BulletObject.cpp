#include "GamePCH.h"
#include "BulletObject.h"
#include "Events/RemoveFromSceneEvent.h"
#include "Game/Game.h"
#include "Game/Scene.h"
#include "Mesh/Mesh.h"


BulletObject::BulletObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_LifeTimeTimer = 0.0f;
    m_DebugDraw = true;
    m_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

BulletObject::~BulletObject()
{

}

void BulletObject::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    m_LifeTimeTimer += deltaTime;
    if (m_LifeTimeTimer > BULLET_LIFETIME)
    {
        m_LifeTimeTimer = 0.0f;
        Event* destroy = new RemoveFromSceneEvent(m_pScene, this);
        m_pScene->GetGame()->GetEventManager()->QueueEvent(destroy);
    }
}

void BulletObject::Draw(CameraObject* pCamera)
{
    if (m_pMesh != nullptr)
    {
        m_pMesh->SetupAttributes(m_pMaterial);

        // Create world matrix.
        MyMatrix worldMat;
        worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);

        MyMatrix rotMat;
        rotMat.CreateRotation(m_Rotation);

        m_pMesh->SetupUniforms(m_pMaterial, &worldMat, &rotMat, pCamera, m_UVScale, m_UVOffset, m_pScene->GetLights(), m_Color);
        SetupUniforms(); //GameObject's set up other uniforms their specific shaders might need.
        m_pMesh->Draw(m_pMaterial);
    }

    m_DebugDraw = m_pScene->GetDebugDraw();
    if (m_DebugDraw)
    {
        //Draw ImGui window for this game object
        GenerateImGuiWindow();
    }
}

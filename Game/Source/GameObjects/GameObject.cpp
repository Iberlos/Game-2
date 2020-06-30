#include "GamePCH.h"

#include "Mesh/Material.h"
#include "Mesh/Mesh.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "Game/Scene.h"
#include "Game/ResourceManager.h"
#include "Physics3D/PhysicsManager.h"
#include "Physics3D/GameObjectMotionState.h"
#include "GameObject.h"
#include "Tweening/Tween.h"
#include "Tweening/TweenFuncs.h"

void GameObject::SetupUniforms()
{
}

GameObject::GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: m_Name( name )
, m_pScene( pScene )
, m_pMesh( pMesh )
, m_pMaterial( pMaterial )
, m_InitialPosition( pos )
, m_InitialRotation( rot )
, m_Position( pos )
, m_Rotation( rot )
, m_Scale( scale )
, m_DebugDraw( true )
{
    m_UVScale.Set( 1.0f, 1.0f );
    m_UVOffset.Set( 0.0f, 0.0f );
    m_Body = nullptr;
    m_MotionState = nullptr;
    m_Pool = nullptr;
}

GameObject::~GameObject()
{
    delete m_MotionState;
    if (m_Body)
    {
        m_pScene->GetPhysicsManager()->GetWorld()->removeRigidBody(m_Body);
        delete m_Body;
    }
    for (unsigned int i = 0; i < m_Tweens.size(); i++)
    {
        delete m_Tweens.at(i);
    }
    m_Tweens.clear();
}

void GameObject::Reset()
{
    SetPosition(m_InitialPosition);
    SetRotation(m_InitialRotation);
}

void GameObject::OnEvent(Event* pEvent)
{
}

void GameObject::Update(float deltaTime)
{
    //Simple test rotation
    //m_Rotation.y += 15.0f *deltaTime;
    for (unsigned int i = 0; i < m_Tweens.size(); i++)
    {
        if (m_Tweens.at(i)->Update(deltaTime))
        {
            delete m_Tweens.at(i);
            m_Tweens.erase(m_Tweens.begin() + i);
            i--;
        }
    }

    mat4 rotation;
    rotation.CreateRotation(m_Rotation);
    m_ForwardVector = rotation.GetAt();
    //m_ForwardVector = vec3(sinf(m_Rotation.y * PI / 180.0f)*cosf(m_Rotation.x * PI / 180.0f), sinf(m_Rotation.x * PI / 180.0f), cosf(m_Rotation.y * PI / 180.0f)*cosf(m_Rotation.x * PI / 180.0f));
}

void GameObject::Draw(CameraObject* pCamera)
{
    if( m_pMesh != nullptr )
    {
        m_pMesh->SetupAttributes( m_pMaterial );

        // Create world matrix.
        MyMatrix worldMat;
        worldMat.CreateSRT( m_Scale, m_Rotation, m_Position );

        MyMatrix rotMat;
        rotMat.CreateRotation(m_Rotation);

        m_pMesh->SetupUniforms( m_pMaterial, &worldMat, &rotMat, pCamera, m_UVScale, m_UVOffset, m_pScene->GetLights());
        SetupUniforms(); //GameObject's set up other uniforms their specific shaders might need.
        m_pMesh->Draw( m_pMaterial );
    }

    m_DebugDraw = m_pScene->GetDebugDraw();
    if (m_DebugDraw)
    {
        //Draw ImGui window for this game object
        GenerateImGuiWindow();
    }
}

void GameObject::SetPosition(vec3 pos)
{
    m_Position = pos;
    if (m_Body)
    {
        btTransform newTransForm = m_Body->getWorldTransform();
        newTransForm.setOrigin(btVector3(pos.x, pos.y, pos.z));
        m_Body->setWorldTransform(newTransForm);
    }
}

void GameObject::SetRotation(vec3 rot)
{
    m_Rotation = rot;
    if (m_Body)
    {
        btTransform newTransForm = m_Body->getWorldTransform();
        newTransForm.setRotation(btQuaternion(rot.x, rot.y, rot.z));
        m_Body->setWorldTransform(newTransForm);
    }
}

void GameObject::SetScale(vec3 scale)
{
    m_Scale = scale;
}

void GameObject::SetUVScaleAndOffset(vec2 uvScale, vec2 uvOffset)
{
    m_UVScale = uvScale;
    m_UVOffset = uvOffset;
}

void GameObject::AddTag(std::string tag)
{
    m_Tags.push_back(tag);
}

void GameObject::AddScaleTween(TweenFunction* tweenFunction, vec3 value, double timeLength)
{
    Tween* scaleTween = new Tween();

    scaleTween->Setup(tweenFunction, &m_Scale, m_Scale, m_Scale + value, timeLength);
    m_Tweens.push_back(scaleTween);
}

void GameObject::AddRotationTween(TweenFunction* tweenFunction, vec3 value, double timeLength)
{
    Tween* rotationTween = new Tween();

    rotationTween->Setup(tweenFunction, &m_Rotation, m_Rotation, m_Rotation + value, timeLength);
    m_Tweens.push_back(rotationTween);
}

void GameObject::ReturnToPool()
{
    if (m_Pool)
    {
        m_Pool->ReturnObject(this);
    }
}

void GameObject::RemoveFromScene()
{
    m_pScene->RemoveGameObject( this );
    ReturnToPool();
}

bool GameObject::ObjectHasTag(std::string tag)
{
    for (unsigned int i = 0; i < m_Tags.size(); i++)
    {
        if (m_Tags.at(i) == tag)
        {
            return true;
        }
    }
    return false;
}

btRigidBody* GameObject::AddRigidBody(btCollisionShape* bodyShape, float mass, bool bLockRotationToY)
{
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(m_Position.x,m_Position.y,m_Position.z));

    btScalar btMass(mass);
    bool isDynamic = (btMass != 0.0f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
    {
        bodyShape->calculateLocalInertia(btMass, localInertia);
    }

    if (bLockRotationToY)
    {
        localInertia = btVector3(0, 1, 0);
    }

    m_MotionState = new GameObjectMotionState(this);
#undef  new
    btRigidBody::btRigidBodyConstructionInfo bodyInfo(btMass, m_MotionState, bodyShape, localInertia);
    m_Body = new btRigidBody(bodyInfo);
    m_Body->setUserPointer(this);

    m_pScene->GetPhysicsManager()->GetWorld()->addRigidBody(m_Body);

    return m_Body;
}

void GameObject::OnContactAdded()
{
}

void GameObject::OnContactStarted(GameObject* otherObject, vec3 worldNormal)
{
    //owww, something hit me
}

void GameObject::OnContactEnded()
{

}

void GameObject::GenerateImGuiWindow()
{
    ImGui::Begin("GameObjects");
    std::string title;
    if (ImGui::CollapsingHeader(m_Name.c_str()))
    {
        ImGui::Indent();
        ImGui::PushID(this);

        if (ImGui::CollapsingHeader("Transform"))
        {
            ImGui::Indent();
            ImGui::DragFloat3("Scale", &m_Scale.x);
            ImGui::DragFloat3("Rotation", &m_Rotation.x);
            ImGui::DragFloat3("Position", &m_Position.x);
            ImGui::Unindent();
        }
        if (m_Body)
        {
            if (ImGui::CollapsingHeader("Physics3D Body"))
            {
                title = "Velocity: " + std::to_string(m_Body->getLinearVelocity().x()) + ", " + std::to_string(m_Body->getLinearVelocity().y()) + ", " + std::to_string(m_Body->getLinearVelocity().z());
                if (ImGui::CollapsingHeader(title.c_str()))
                {
                    ImGui::Text("Vel X: %f", m_Body->getLinearVelocity().x());
                    ImGui::Text("Vel Y: %f", m_Body->getLinearVelocity().y());
                    ImGui::Text("Vel Z: %f", m_Body->getLinearVelocity().z());
                }
                title = "Angular Velocity: " + std::to_string(m_Body->getAngularVelocity().x()) + ", " + std::to_string(m_Body->getAngularVelocity().y()) + ", " + std::to_string(m_Body->getAngularVelocity().z());
                if (ImGui::CollapsingHeader(title.c_str()))
                {
                    ImGui::Text("AVel X: %f", m_Body->getAngularVelocity().x());
                    ImGui::Text("AVel Y: %f", m_Body->getAngularVelocity().y());
                    ImGui::Text("AVel Z: %f", m_Body->getAngularVelocity().z());
                }
                if (ImGui::CollapsingHeader("Mass Properties"))
                {
                    ImGui::Text("Mass: %f", m_Body->getInvMass());
                    ImGui::Text("Inertia X: %f", m_Body->getLocalInertia().x());
                    ImGui::Text("Inertia X: %f", m_Body->getLocalInertia().y());
                    ImGui::Text("Inertia X: %f", m_Body->getLocalInertia().z());
                }
                if (ImGui::CollapsingHeader("Collision Properties"))
                {
                    ImGui::Text("Static: %d", m_Body->isStaticObject());
                    ImGui::Text("Kinematic: %d", m_Body->isKinematicObject());
                    ImGui::Text("In world: %d", m_Body->isInWorld());
                }
            }
        }

        ImGui::PopID();
        ImGui::Unindent();
    }
    ImGui::End();
}

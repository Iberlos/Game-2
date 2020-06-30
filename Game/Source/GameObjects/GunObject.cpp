#include "GamePCH.h"
#include "GunObject.h"
#include "Events/GameEvent.h"
#include "Tweening/Tween.h"

GunObject::GunObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_DebugDraw = true;
    m_TimeRemaining = -1.0f;
    m_WhichTween = 1;
    m_TweenFunction = TweenFunc_SineEaseIn;
    m_KickTime = ANIM_TIME;
    m_ResetTime = ANIM_TIME * 4.0f;
}

GunObject::~GunObject()
{

}

void GunObject::OnEvent(Event* pEvent)
{
    if (pEvent->GetEventType() == EventType_GamePlay)
    {
        GameEvent* pGameEvent = static_cast<GameEvent*>(pEvent);
        if (pGameEvent->GetGameEventType() == GameEventType_PlayerFire)
        {
            AddRotationTween(m_TweenFunction, vec3(-10.0f, 0.0f, 0.0f), m_KickTime);
            m_TimeRemaining = m_KickTime;
        }
    }
}

void GunObject::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    if (m_TimeRemaining >= 0.0f)
    {
        m_TimeRemaining -= deltaTime;
        if (m_TimeRemaining <= 0.0f)
        {
            AddRotationTween(TweenFunc_Linear, vec3(10.0f, 0.0f, 0.0f), m_ResetTime);
        }
    }
}

void GunObject::GenerateImGuiWindow()
{
    ImGui::Begin("GameObjects");
    std::string title;
    if (ImGui::CollapsingHeader(m_Name.c_str()))
    {
        ImGui::Indent();
        ImGui::PushID(this);

        if (ImGui::CollapsingHeader("Tween Functions"))
        {
            ImGui::DragFloat("KickTime", &m_KickTime, 0.05f);
            ImGui::DragFloat("ResetTime", &m_ResetTime, 0.05f);
            const char* soundTypes[] = { "Linear", "SineEaseIn", "SineEaseOut", "SineEaseInOut", "BounceEaseIn", "BounceEaseOut", "BounceEaseInOut", "ElasticEaseIn", "ElasticEaseOut", "ElasticEaseInOut" };

            if (ImGui::BeginCombo("##combo", soundTypes[m_WhichTween]))
            {
                for (int i = 0; i < NUM_TWEENS; i++)
                {
                    bool is_selected = (m_WhichTween == i);
                    if (ImGui::Selectable(soundTypes[i], is_selected))
                    {
                        m_WhichTween = i;
                    }
                }
                ImGui::EndCombo();
            }

            switch (m_WhichTween)
            {
            case 0:
            {
                m_TweenFunction = TweenFunc_Linear;
                break;
            }
            case 1:
            {
                m_TweenFunction = TweenFunc_SineEaseIn;
                break;
            }
            case 2:
            {
                m_TweenFunction = TweenFunc_SineEaseOut;
                break;
            }
            case 3:
            {
                m_TweenFunction = TweenFunc_SineEaseInOut;
                break;
            }
            case 4:
            {
                m_TweenFunction = TweenFunc_BounceEaseIn;
                break;
            }
            case 5:
            {
                m_TweenFunction = TweenFunc_BounceEaseOut;
                break;
            }
            case 6:
            {
                m_TweenFunction = TweenFunc_BounceEaseInOut;
                break;
            }
            case 7:
            {
                m_TweenFunction = TweenFunc_ElasticEaseIn;
                break;
            }
            case 8:
            {
                m_TweenFunction = TweenFunc_ElasticEaseOut;
                break;
            }
            case 9:
            {
                m_TweenFunction = TweenFunc_ElasticEaseInOut;
                break;
            }
            }
        }

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

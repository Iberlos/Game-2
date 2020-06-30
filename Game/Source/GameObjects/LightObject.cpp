#include "GamePCH.h"
#include "LightObject.h"

Light::Light(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
:GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
,m_color(1.0f, 1.0f, 1.0f)
,m_falloff(10.0f)
,m_Target(nullptr)
,m_FollowDistance(3)
{
    m_Tags.push_back("Light");
    m_IsActive = true;
}

void Light::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    if (m_Target)
    {
        m_Rotation = m_Target->GetRotation();
        SetPosition(m_Target->GetPosition() - vec3(cosf((m_Rotation.y + 90)*PI / 180) * cosf(m_Rotation.x*PI / 180), sinf(m_Rotation.x*PI / 180), sinf((m_Rotation.y + 90)*PI / 180) * cosf(m_Rotation.x*PI / 180))*m_FollowDistance);
    }
}

void Light::Draw(CameraObject * pCamera)
{
    GameObject::Draw(pCamera);
}

void Light::GenerateImGuiWindow()
{
    ImGui::Begin("GameObjects");
    std::string title;
    if (ImGui::CollapsingHeader(m_Name.c_str()))
    {
        ImGui::Indent();
        ImGui::PushID(this);

        if (ImGui::CollapsingHeader("Light Settings"))
        {
            ImGui::ColorEdit3("Color", &m_color.x);
            ImGui::DragFloat("Falloff", &m_falloff);
            ImGui::DragFloat3("Position", &m_Position.x);
            ImGui::Checkbox("Is Active", &m_IsActive);
            if (m_Target)
            {
                std::string title = "Target: " + m_Target->GetName();
                if (ImGui::CollapsingHeader(title.c_str()))
                {
                    ImGui::DragFloat("Attach Offset", &m_FollowDistance);
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

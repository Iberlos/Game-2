#include "GamePCH.h"
#include "GunScene.h"
#include "Game/Game.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/LightObject.h"
#include "Game/ResourceManager.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GunObject.h"
#include "FBOs/FBODefinition.h"

GunScene::GunScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer)
    : Scene(a_Name, pGame, pResources, pPlayer)
{
    m_IsOpaque = false;
}

GunScene::~GunScene()
{

}

void GunScene::LoadContent()
{
    Scene::LoadContent();

    //Below includes magic numbers for placing gun + light on screen

    GameObject* gun = new GunObject(this, "Handgun", vec3(4.0f, -10.0f, 25.0f), vec3(0.0f, -176.0f, 0.0f), vec3(1.0f), m_pResources->GetMesh("Handgun"), m_pResources->GetMaterial("Handgun"));
    AddGameObject(gun);

    Light* light = new Light(this, "GunLight", vec3(0.0f, 0.0f, 15.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.1f, 0.1f, 0.1f), nullptr, nullptr);
    light->SetFalloff(48.0f);
    AddGameObject(light);

    CameraObject* camera = new CameraObject(this, "Camera", vec3(0, 0, 0.0f), vec3(0.0f), vec3(1));
    AddGameObject(camera);
}

void GunScene::Draw()
{
    Scene::Draw();
}

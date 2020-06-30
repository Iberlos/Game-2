#include "GamePCH.h"

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for( auto object: m_pMeshes )
        delete object.second;

    for( auto object: m_pMaterials )
        delete object.second;

    for( auto object: m_pShaders )
        delete object.second;

    for( auto object: m_pTextures )
        delete object.second;

    for (auto object : m_pSounds)
        delete object.second;

    for (auto object : m_pSoundCues)
        delete object.second;

    for (auto object : m_pCollisionShapes)
        delete object.second;
}

void ResourceManager::GenerateImGuiWindow()
{
    ImGui::Begin("ResourceManager");
    if (ImGui::CollapsingHeader("SoundCues"))
    {
        ImGui::Indent();
        for (auto object : m_pSoundCues)
        {
            object.second->GenerateImGuiWindow();
        }
        ImGui::Unindent();
    }
    ImGui::End();
}

Mesh* ResourceManager::AddMesh(std::string name, Mesh* pMesh)
{
    assert( m_pMeshes.find( name ) == m_pMeshes.end() );

    m_pMeshes[name] = pMesh;

    return pMesh;
}

void ResourceManager::AddShader(std::string name, ShaderProgram* pShader)
{
    assert( m_pShaders.find( name ) == m_pShaders.end() );

    m_pShaders[name] = pShader;
}

void ResourceManager::AddTexture(std::string name, Texture* pTexture)
{
    assert( m_pTextures.find( name ) == m_pTextures.end() );

    m_pTextures[name] = pTexture;
}

void ResourceManager::AddMaterial(std::string name, Material* pMaterial)
{
    assert( m_pMaterials.find( name ) == m_pMaterials.end() );

    m_pMaterials[name] = pMaterial;
}

void ResourceManager::AddSound(std::string name, SoundObject* pSound)
{
    assert(m_pMaterials.find(name) == m_pMaterials.end());

    m_pSounds[name] = pSound;
}

void ResourceManager::AddSoundCue(std::string name, SoundCue* pSoundCue)
{
    assert(m_pMaterials.find(name) == m_pMaterials.end());

    m_pSoundCues[name] = pSoundCue;
}

void ResourceManager::AddCollisionShape(std::string name, btCollisionShape* pCollisionShape)
{
    assert(m_pCollisionShapes.find(name) == m_pCollisionShapes.end());

    m_pCollisionShapes[name] = pCollisionShape;
}

Mesh* ResourceManager::GetMesh(std::string name)
{
    auto it = m_pMeshes.find( name );
    if( it == m_pMeshes.end() )
        return nullptr;

    return it->second;
}

ShaderProgram* ResourceManager::GetShader(std::string name)
{
    auto it = m_pShaders.find( name );
    if( it == m_pShaders.end() )
        return nullptr;

    return it->second;
}

Texture* ResourceManager::GetTexture(std::string name)
{
    auto it = m_pTextures.find( name );
    if( it == m_pTextures.end() )
        return nullptr;

    return it->second;
}

Material* ResourceManager::GetMaterial(std::string name)
{
    auto it = m_pMaterials.find( name );
    if( it == m_pMaterials.end() )
        return nullptr;

    return it->second;
}

SoundObject* ResourceManager::GetSound(const std::string name)
{
    auto it = m_pSounds.find(name);
    if (it == m_pSounds.end())
        return nullptr;

    return it->second;
}

SoundCue* ResourceManager::GetSoundCue(const std::string name)
{
    auto it = m_pSoundCues.find(name);
    if (it == m_pSoundCues.end())
        return nullptr;

    return it->second;
}

btCollisionShape* ResourceManager::GetCollisionShape(const std::string name)
{
    auto it = m_pCollisionShapes.find(name);
    if (it == m_pCollisionShapes.end())
        return nullptr;

    return it->second;
}

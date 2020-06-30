#include "GamePCH.h"

#include "Material.h"
#include "Mesh/Texture.h"

Material::Material(ShaderProgram* pShader, Texture* pTexture, Texture* pCubeMapTexture)
{
    m_pShader = pShader;
    m_pTexture = pTexture;
    m_pCubeTexture = pCubeMapTexture;
}

Material::~Material()
{
}

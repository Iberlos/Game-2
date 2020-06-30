#include "GamePCH.h"
#include "SpriteFont.h"
#include "../Mesh/Mesh.h"
#include "Mesh/Material.h"
#include "Game/Scene.h"
#include "Game/SceneManager.h"
#include "GameObjects/CameraObject.h"
#include "../Mesh/FontSpritesheet.h"

SpriteFont::SpriteFont(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, FontSpritesheet* spritesheet, std::string text) : UIObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_Spritesheet = spritesheet;
    m_Text = text;
    m_KerningAmount = 0.0f;
}

SpriteFont::~SpriteFont()
{
}

void SpriteFont::Draw(CameraObject* pCamera)
{
    //if (m_pMesh != nullptr)
    //{
    //    //OLD CODE
    //    vec2 letterPorportions = 0.0f;
    //    vec2 trackingOffset = 0.0f;

    //    for (unsigned int i = 0; i < m_Text.length(); i++)
    //    {
    //        m_pMesh->SetupAttributes(m_pMaterial);
    //        SpriteInfo* theSprite = m_Spritesheet->GetSprite(std::string(1, m_Text.at(i)));
    //        letterPorportions = theSprite->uvScale * m_Spritesheet->GetSpritesheetSize();
    //        /*m_Mesh->Draw(m_Position + kerningOffset, m_Angle, m_Scale*fontScale, camPos, projScale, m_TextureID, theSprite);*/

    //        mat4 objMatrix;
    //        vec3 posOffset = 0;
    //        posOffset.x = (trackingOffset.x + theSprite->bearing.x) * m_Scale.x;
    //        objMatrix.CreateSRT(m_Scale*letterPorportions, m_Rotation, m_Position + posOffset);

    //        m_pMesh->SetupUniforms(m_pMaterial, &objMatrix, pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix(), m_pMaterial->GetTexture(), nullptr, theSprite);
    //        m_pMesh->Draw(m_pMaterial->GetShader());
    //        trackingOffset.x += (theSprite->advanceX);//(theSprite->advanceX) * m_Scale.x + m_KerningAmount;
    //    }
    //}
}
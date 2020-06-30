#pragma once
#include "../GameObjects/UIObject.h"

//Forward Declarations
class Mesh;
class FontSpritesheet;

class SpriteFont : public UIObject
{
public:
    SpriteFont(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, FontSpritesheet* spritesheet, std::string text);
    virtual ~SpriteFont();

    virtual void Draw(CameraObject* pCamera) override;

    void SetText(std::string text) { m_Text = text; }
    void SetKerningAmount(float kerning) { m_KerningAmount = kerning; }
    std::string GetText() { return m_Text; }

private:
    Mesh * m_Mesh;
    GLuint m_TextureID;
    FontSpritesheet* m_Spritesheet;
    std::string m_Text;
    float m_KerningAmount;
};

#ifndef __Material_H__
#define __Material_H__

class ShaderProgram;
class Texture;

class Material
{
protected:
    ShaderProgram* m_pShader;
    Texture* m_pTexture;
    Texture* m_pCubeTexture;

public:
    Material(ShaderProgram* pShader, Texture* pTexture, Texture* pCubeMapTexture = nullptr);
    virtual ~Material();

    void SetShader(ShaderProgram* a_shader) { m_pShader = a_shader; }
    ShaderProgram* GetShader() { return m_pShader; }
    Texture* GetTexture() { return m_pTexture; }
    Texture* GetCubeTexture() { return m_pCubeTexture; };
};

#endif //__Material_H__

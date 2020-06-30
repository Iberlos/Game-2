#ifndef __Texture_H__
#define __Texture_H__

class Texture
{
protected:
    GLuint m_TextureID;
    unsigned int m_Width;
    unsigned int m_Height;

public:
    Texture(const char* filename);
    //Texture(const char** filenames);
    Texture(GLuint FBO, unsigned int width, unsigned int height);
    Texture(const char** filename);
    virtual ~Texture();

    GLuint GetTextureID() { return m_TextureID; }
    unsigned int GetWidth() { return m_Width; }
    unsigned int GetHeight() { return m_Height; }
};

#endif //__Texture_H__

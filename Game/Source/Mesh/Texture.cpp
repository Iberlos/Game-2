#include "GamePCH.h"

#include "Mesh/Texture.h"

Texture::Texture(const char* filename)
{
    m_TextureID = LoadTexture( filename, &m_Width, &m_Height );
    int i = 0;
}

//Texture::Texture(const char* filenames[])
//{
//    m_TextureID = LoadTextureCubemap(filenames);
//}

Texture::Texture(GLuint FBO, unsigned int width, unsigned int height)
{
    m_TextureID = FBO;
    m_Width = width;
    m_Height = height;
}

Texture::Texture(const char** filename)
{
    m_TextureID = LoadTextureCubemap(filename);
    m_Width = 0;
    m_Height = 0;
}

Texture::~Texture()
{
    glDeleteTextures( 1, &m_TextureID );
}

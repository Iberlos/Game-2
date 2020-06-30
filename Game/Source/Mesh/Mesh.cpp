#include "GamePCH.h"

#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "VertexFormat.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/LightObject.h"
#include "Game/Scene.h"
#include "Game/Game.h"

Mesh::Mesh()
{
    m_VBO = 0;
    m_IBO = 0;

    m_NumVerts = 0;
    m_NumIndices = 0;

    m_PrimitiveType = -1;
}

Mesh::~Mesh()
{
    glDeleteBuffers( 1, &m_VBO );
    glDeleteBuffers( 1, &m_IBO );
}

void Mesh::Init(VertexFormat* verts, int numVerts, unsigned int* indices, int numIndices, GLenum primitiveType, GLenum usage)
{
    assert( numVerts != 0 );

    m_NumVerts = numVerts;
    m_NumIndices = numIndices;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*numVerts, verts, usage );

    // Generate and fill buffer with our indices.
    if( m_IBO == 0 )
        glGenBuffers( 1, &m_IBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numIndices, indices, usage );

    CheckForGLErrors();
}

void Mesh::Init(const void* verts, int numVerts, GLenum primitiveType, GLenum usage)
{
    m_NumVerts = numVerts;
    m_NumIndices = 0;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat) * numVerts, verts, usage );

    CheckForGLErrors();
}

void SetUniform1f(GLuint shader, const char* uniformName, float value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform1f( loc, value );
    }
}

void SetUniform2f(GLuint shader, const char* uniformName, vec2 value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform2f( loc, value.x, value.y );
    }
}

void SetUniform2i(GLuint shader, const char* uniformName, ivec2 value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform2i(loc, value.x, value.y);
    }
}

void SetUniform3f(GLuint shader, const char* uniformName, vec3 value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform3f( loc, value.x, value.y, value.z );
    }
}

void SetUniform4f(GLuint shader, const char* uniformName, vec4 value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform4f(loc, value.x, value.y, value.z, value.w);
    }
}

void Mesh::SetupAttributes(Material* pMaterial)
{
    assert( m_VBO != 0 );
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );
    CheckForGLErrors();

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Bind buffer and set up attributes.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    GLint loc = glGetAttribLocation( shader, "a_Position" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<void*>( offsetof(VertexFormat, m_Pos) ) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_Color" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), reinterpret_cast<void*>( offsetof(VertexFormat, m_Color) ) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_UV" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<void*>( offsetof(VertexFormat, m_UV) ) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation(shader, "a_Normal");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<void*>(offsetof(VertexFormat, m_Normal)));
        glEnableVertexAttribArray(loc);
    }
}

void Mesh::SetupUniforms(Material* pMaterial, mat4* worldMat, mat4* rotMat, CameraObject* pCamera, vec2 uvScale, vec2 uvOffset, std::vector<Light*> lights, vec4 color)
{
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );
    CheckForGLErrors();

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Set up shader.
    glUseProgram( shader );

    // Set up uniforms.
    GLint loc;
    loc = glGetUniformLocation( shader, "u_WorldMatrix" );
    glUniformMatrix4fv(loc, 1, false, &worldMat->m11);

    loc = glGetUniformLocation(shader, "u_RotationMatrix");
    glUniformMatrix4fv(loc, 1, false, &rotMat->m11);

    loc = glGetUniformLocation( shader, "u_ViewMatrix" );
    glUniformMatrix4fv( loc, 1, false, &pCamera->GetViewMatrix()->m11 );

    loc = glGetUniformLocation( shader, "u_ProjectionMatrix" );
    glUniformMatrix4fv( loc, 1, false, &pCamera->GetProjMatrix()->m11 );

    SetUniform2f( shader, "u_UVScale", uvScale );
    SetUniform2f( shader, "u_UVOffset", uvOffset );

    SetUniform1f( shader, "u_Time", (float)GetSystemTimeSinceGameStart() );

    SetUniform3f(shader, "u_CameraPos", pCamera->GetPosition());

    SetUniform4f(shader, "u_Color", color);

    //Light stuff
    //Number of lights
    int activeLightsBits = 0;
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        if (lights.at(i)->GetIsActive())
        {
            activeLightsBits |= (int)(1 * pow(2, i));
        }
    }
    loc = glGetUniformLocation(shader, "u_ActiveLights");
    glUniform1i(loc, activeLightsBits);
    //Positions
    loc = glGetUniformLocation(shader, "u_LightPos");
    vec3 lightPositions[NUM_LIGHTS];
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        lightPositions[i] = lights.at(i)->GetPosition();
    }
    glUniform3fv(loc, NUM_LIGHTS, &lightPositions[0].x);
    //Colors
    loc = glGetUniformLocation(shader, "u_LightColor");
    vec3 lightColors[NUM_LIGHTS];
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        lightColors[i] = lights.at(i)->GetColor();
    }
    glUniform3fv(loc, NUM_LIGHTS, &lightColors[0].x);
    //Ranges
    loc = glGetUniformLocation(shader, "u_LightRange");
    float lightRanges[NUM_LIGHTS];
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        lightRanges[i] = lights.at(i)->GetFalloff();
    }
    glUniform1fv(loc, NUM_LIGHTS, &lightRanges[0]);

    // Setup our texture.
    Texture* pTexture = pMaterial->GetTexture();
    if( pTexture != nullptr )
    {
        int textureUnitIndex = 0;
        glActiveTexture( GL_TEXTURE0 + textureUnitIndex );
        glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );
        GLint loc = glGetUniformLocation( shader, "u_Texture" );
        if( loc != -1 )
        {
            glUniform1i( loc, textureUnitIndex );
        }
        SetUniform2f(shader, "u_TextureSize", vec2((float)pTexture->GetWidth(), (float)pTexture->GetHeight()));
    }

    //set up cubemap
    Texture* pCubeTexture = pMaterial->GetCubeTexture();
    if (pCubeTexture != nullptr)
    {
        int textureUnitIndex = 1;
        glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, pCubeTexture->GetTextureID());
        GLint loc = glGetUniformLocation(shader, "u_TextureCube");
        if (loc != -1)
        {
            glUniform1i(loc, textureUnitIndex);
        }
    }

    SetUniform2f(shader, "u_WindowSize", vec2((float)pCamera->GetScene()->GetGame()->GetFramework()->GetWindowWidth(), (float)pCamera->GetScene()->GetGame()->GetFramework()->GetWindowHeight()));

    CheckForGLErrors();
}

void Mesh::Draw(Material* pMaterial)
{
    assert( m_PrimitiveType != -1 );
    assert( m_NumVerts != 0 );
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );
    CheckForGLErrors();

    // Draw.
    if( m_NumIndices > 0 )
    {
        glDrawElements( m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
    }

    // Disable the attribute arrays used.
    {
        GLuint shader = pMaterial->GetShader()->GetProgram();

        GLint aPos = glGetAttribLocation( shader, "a_Position" );
        GLint aColor = glGetAttribLocation( shader, "a_Color" );
        GLint aUV = glGetAttribLocation( shader, "a_UV" );

        glDisableVertexAttribArray( aPos );

        if( aColor != -1 )
            glDisableVertexAttribArray( aColor );

        if( aUV != -1 )
            glDisableVertexAttribArray( aUV );
    }

    CheckForGLErrors();
}

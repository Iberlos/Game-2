#ifndef __Mesh_H__
#define __Mesh_H__

class CameraObject;
class Material;
class Texture;
class VertexFormat;
class Light;

const int NUM_LIGHTS = 4;

void SetUniform1f(GLuint shader, const char* uniformName, float value);
void SetUniform2f(GLuint shader, const char* uniformName, vec2 value);
void SetUniform2i(GLuint shader, const char* uniformName, ivec2 value);
void SetUniform3f(GLuint shader, const char* uniformName, vec3 value);
void SetUniform4f(GLuint shader, const char* uniformName, vec4 value);


class Mesh
{

protected:
    GLuint m_VBO;
    GLuint m_IBO;

    unsigned int m_NumVerts;
    unsigned int m_NumIndices;

    GLenum m_PrimitiveType;

public:
    Mesh();
    virtual ~Mesh();

    void Init(VertexFormat* verts, int numVerts, unsigned int* indices, int numIndices, GLenum primitiveType, GLenum usage);
    void Init(const void* verts, int numVerts, GLenum primitiveType, GLenum usage);

    void SetupAttributes(Material* pMaterial);
    static void SetupUniforms(Material* pMaterial, mat4* worldMat, mat4* rotMat, CameraObject* pCamera, vec2 uvScale, vec2 uvOffset, std::vector<Light*> lights, vec4 color = vec4(1, 1, 1, 1));
    void Draw(Material* pMaterial);

    // The following functions are defined in MeshShapes.cpp:
    void CreateBox(vec2 size, vec2 offset);
    void CreateBoxWithFlippedHorizontalUVs(vec2 size, vec2 offset);
    void CreateCube(vec3 size);
    void CreatePlane(vec2 worldSize, ivec2 vertexCount, vec2 pivotPoint, vec2 uvRepeat = 5);
    void CreateOBJ(const char* objFilename, vec3 scale);
    void CreateRing(float innerradius, float outerradius, int numsegments, MyColor color);
    void CreateArc(float outerradius, int degrees, int numsegments, MyColor color);
};

#endif //__Mesh_H__

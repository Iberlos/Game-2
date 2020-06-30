#include "GamePCH.h"
#include "DebugDraw.h"

#include "Mesh/Material.h"
#include "Mesh/Mesh.h"
#include "GameObjects/CameraObject.h"

DebugDraw::DebugDraw() : btIDebugDraw()
{
    m_Mode = DBG_NoDebug;
}

DebugDraw::~DebugDraw()
{

}

void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
    //Generate vertice positions
    btVector3 points[2] = { from,to };

    //GL stuff
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLint loc = glGetAttribLocation(m_Mat->GetShader()->GetProgram(), "a_Position");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(btVector3), points);
        glEnableVertexAttribArray(loc);
    }

    mat4 identiy;
    identiy.SetIdentity();
    std::vector<Light*> emptyLights;
    //Mesh::SetupUniforms(m_Mat->GetShader(), &world, m_Camera->GetViewMatrix(), m_Camera->GetProjectionMatrix(), m_Mat->GetTexture(), &MyColor((unsigned char)(color.r * 255), (unsigned char)(color.g * 255), (unsigned char)(color.b * 255), (unsigned char)(0.5f * 255)));
    Mesh::SetupUniforms(m_Mat, &identiy, &identiy, m_Camera, vec2(0), vec2(0), emptyLights, vec4(color.x(), color.y(), color.z(), 0.5f));

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, 2);
    glLineWidth(1.0f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void DebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
    //Generate vertice positions
    btVector3 points[2] = { PointOnB, PointOnB + normalOnB * distance };

    //GL stuff
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLint loc = glGetAttribLocation(m_Mat->GetShader()->GetProgram(), "a_Position");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(btVector3), points);
        glEnableVertexAttribArray(loc);
    }

    mat4 identiy;
    identiy.SetIdentity();
    std::vector<Light*> emptyLights;
    Mesh::SetupUniforms(m_Mat, &identiy, &identiy, m_Camera, vec2(0), vec2(0), emptyLights, vec4(color.x(), color.y(), color.z(), 0.5f));

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, 1);
    glPointSize(1.0f);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, 2);
    glLineWidth(1.0f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void DebugDraw::reportErrorWarning(const char* warningString)
{
    OutputMessage("DebugDraw warning: %s",  warningString);
}

void DebugDraw::draw3dText(const btVector3& location, const char* textString)
{
    //NOTHING
}

void DebugDraw::setDebugMode(int debugMode)
{
    m_Mode = debugMode;
}

int DebugDraw::getDebugMode() const
{
    return m_Mode;
}

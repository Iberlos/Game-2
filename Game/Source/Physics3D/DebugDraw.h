#pragma once

class Material;
class CameraObject;

class DebugDraw : public btIDebugDraw
{
public:
    DebugDraw();
    ~DebugDraw();

    void SetDebugDrawMat(Material* mat) { m_Mat = mat; }
    void SetDebugCamera(CameraObject* camera) { m_Camera = camera; }

    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;

    virtual void reportErrorWarning(const char* warningString) override;
    virtual void draw3dText(const btVector3& location, const char* textString) override;
    virtual void setDebugMode(int debugMode) override;
    virtual int getDebugMode() const override;

protected:
    Material* m_Mat;
    CameraObject* m_Camera;
    unsigned int m_Mode;

};
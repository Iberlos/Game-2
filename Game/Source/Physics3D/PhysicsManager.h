#pragma once

class DebugDraw;
class Material;
class CameraObject;

class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();

    void Update(float deltaTime);
    void Draw();

    void SetDebugDrawMat(Material* mat);
    void SetDebugCamera(CameraObject* camera);
    void SetImGuiDebugDraw(bool debugDraw) { m_bImGuiDraw = debugDraw; }

    btDiscreteDynamicsWorld* GetWorld() { return m_World; }

    //ImGui
    virtual void GenerateImGuiWindow();

protected:
    btDiscreteDynamicsWorld* m_World;
    btDefaultCollisionConfiguration* m_CollisionConfiguration;
    btCollisionDispatcher* m_Dispatcher;
    btBroadphaseInterface* m_OverlappingPairCache;
    btSequentialImpulseConstraintSolver* m_Solver;
    DebugDraw* m_DebugDraw;
    unsigned int m_DebugMode;
    bool m_bImGuiDraw;
};
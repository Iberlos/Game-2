#include "GamePCH.h"
#include "PhysicsManager.h"
#include "CollisionCallbacks.h"
#include "DebugDraw.h"

PhysicsManager::PhysicsManager()
{
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    m_CollisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a different dispatcher (see Extras/BulletMultiThreaded)
    m_Dispatcher = new btCollisionDispatcher(m_CollisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    m_OverlappingPairCache = new btDbvtBroadphase();

    m_DebugDraw = new DebugDraw();
    m_DebugMode = 0;

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
#undef  new
    m_Solver = new btSequentialImpulseConstraintSolver();

    m_World = new btDiscreteDynamicsWorld(m_Dispatcher, m_OverlappingPairCache, m_Solver, m_CollisionConfiguration);

    m_World->setDebugDrawer(m_DebugDraw);

    m_World->setGravity(btVector3(0, -9.8f, 0));

    gContactAddedCallback = Game2ContactAddedCallback;
    gContactStartedCallback = Game2ContactStartedCallback;
    gContactEndedCallback = Game2ContactEndedCallback;

    m_bImGuiDraw = true;
}

PhysicsManager::~PhysicsManager()
{
    delete m_World;
    delete m_Solver;
    delete m_DebugDraw;
    delete m_OverlappingPairCache;
    delete m_Dispatcher;
    delete m_CollisionConfiguration;
}

void PhysicsManager::Update(float deltaTime)
{
    m_World->stepSimulation(deltaTime, 10);
}

void PhysicsManager::Draw()
{
    m_World->debugDrawWorld();

    if (m_bImGuiDraw)
        GenerateImGuiWindow();
}

void PhysicsManager::SetDebugDrawMat(Material* mat)
{
    m_DebugDraw->SetDebugDrawMat(mat);
}

void PhysicsManager::SetDebugCamera(CameraObject* camera)
{
    m_DebugDraw->SetDebugCamera(camera);
}

void PhysicsManager::GenerateImGuiWindow()
{
    ImGui::Begin("Debug Settings");
    if (ImGui::CollapsingHeader("PhysicsManager"))
    {
        if (ImGui::CollapsingHeader("DebugDraw Flags"))
        {
            ImGui::CheckboxFlags("Wireframe", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawWireframe);
            ImGui::CheckboxFlags("Aabb", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawAabb);
            ImGui::CheckboxFlags("Features Text", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawFeaturesText);
            ImGui::CheckboxFlags("Contact Points", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawContactPoints);
            ImGui::CheckboxFlags("No Deactivation", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_NoDeactivation);
            ImGui::CheckboxFlags("No Help Text", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_NoHelpText);
            ImGui::CheckboxFlags("Text", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawText);
            ImGui::CheckboxFlags("Profile Timings", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_ProfileTimings);
            ImGui::CheckboxFlags("Enable Sat Comparison", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_EnableSatComparison);
            ImGui::CheckboxFlags("Disable Bullet LCP", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DisableBulletLCP);
            ImGui::CheckboxFlags("Enable CCD", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_EnableCCD);
            ImGui::CheckboxFlags("Constraints", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawConstraints);
            ImGui::CheckboxFlags("Constraint Limits", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawConstraintLimits);
            ImGui::CheckboxFlags("Fast Wireframe", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_FastWireframe);
            ImGui::CheckboxFlags("Normals", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawNormals);
            ImGui::CheckboxFlags("Frames", &m_DebugMode, btIDebugDraw::DebugDrawModes::DBG_DrawFrames);
        }
    }
    ImGui::End();

    m_DebugDraw->setDebugMode(m_DebugMode);
}

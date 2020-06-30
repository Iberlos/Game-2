#ifndef __GameObject_H__
#define __GameObject_H__

#include "Tweening/TweenFuncs.h"
#include "Game/ObjectPool.h"

class Game;
class Material;
class Scene;
class Mesh;
class b2Body;
class CameraObject;
class Tween;

class GameObject
{
    friend class GameObjectMotionState;

protected:
    std::string m_Name;
    std::vector<std::string> m_Tags;

    Scene* m_pScene;
    ObjectPool<GameObject*>* m_Pool;

    Mesh* m_pMesh;
    Material* m_pMaterial;

    vec3 m_InitialPosition;
    vec3 m_InitialRotation;

    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_Scale;
    vec3 m_ForwardVector;

    vec2 m_UVScale;
    vec2 m_UVOffset;

    btRigidBody* m_Body;
    GameObjectMotionState* m_MotionState;

    std::vector<Tween*> m_Tweens;

    virtual void SetupUniforms();

    //Debug
    bool m_DebugDraw;
public:
    GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~GameObject();

    virtual void Reset();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltaTime);
    virtual void Draw(CameraObject* pCamera);

    // Getters.
    std::string GetName() { return m_Name; }
    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetForwardVector() { return m_ForwardVector; }
    Scene* GetScene() { return m_pScene; }

    // Setters.
    void SetPosition(vec3 pos);
    void SetRotation(vec3 rot);
    void SetScale(vec3 scale);
    void SetUVScaleAndOffset(vec2 uvScale, vec2 uvOffset);
    void SetPool(ObjectPool<GameObject*>* pool) { m_Pool = pool; }
    void AddTag(std::string tag);

    //Tween functions
    void AddScaleTween(TweenFunction* tweenFunction, vec3 value, double timeLength);
    void AddRotationTween(TweenFunction* tweenFunction, vec3 value, double timeLength);

    // Other helpers.
    virtual void ReturnToPool();
    virtual void RemoveFromScene();
    virtual bool ObjectHasTag(std::string tag);

    //Physics
    btRigidBody* AddRigidBody(btCollisionShape* shape, float mass = 1.0f, bool resetLocalInertia = false);
    virtual void OnContactAdded();
    virtual void OnContactStarted(GameObject* otherObject, vec3 worldNormal);
    virtual void OnContactEnded();

    //ImGui
    virtual void GenerateImGuiWindow();
};

#endif //__GameObject_H__

#include "GamePCH.h"
#include "GameObjectMotionState.h"
#include "GameObjects/GameObject.h"

GameObjectMotionState::GameObjectMotionState(GameObject* gameObject)
{
    m_Object = gameObject;
}

void GameObjectMotionState::getWorldTransform(btTransform& worldTrans) const
{
    vec3 objectPos = m_Object->GetPosition();
    vec3 objectRotation = m_Object->GetRotation();
    worldTrans.setOrigin(btVector3(objectPos.x, objectPos.y, objectPos.z));
    btQuaternion objectRot = btQuaternion(objectRotation.y, objectRotation.x, objectRotation.z);
    worldTrans.setRotation(objectRot);
}

void GameObjectMotionState::setWorldTransform(const btTransform& worldTrans)
{
    MyMatrix matBulletGL;
    worldTrans.getOpenGLMatrix(&matBulletGL.m11);

    m_Object->m_Position = matBulletGL.GetTranslation();
    m_Object->m_Rotation = matBulletGL.GetEulerAngles() * 180.0f / PI;
}

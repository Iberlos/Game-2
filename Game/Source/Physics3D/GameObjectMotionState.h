#pragma once

class GameObject;

class GameObjectMotionState : public btMotionState
{
protected:
    GameObject* m_Object;

public:
    virtual void getWorldTransform(btTransform& worldTrans) const override;
    virtual void setWorldTransform(const btTransform& worldTrans) override;

    GameObjectMotionState(GameObject* gameObject);

};
#include "GamePCH.h"
#include "CollisionCallbacks.h"
#include "GameObjects/GameObject.h"

bool Game2ContactAddedCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
    return false;
}

void Game2ContactStartedCallback(btPersistentManifold* const& manifold)
{
    btVector3 normal = manifold->getContactPoint(0).m_normalWorldOnB;
    GameObject* object0 = static_cast<GameObject*>(manifold->getBody0()->getUserPointer());
    GameObject* object1 = static_cast<GameObject*>(manifold->getBody1()->getUserPointer());
    object0->OnContactStarted(object1, vec3(normal.x(), normal.y(), normal.z()));
    //normal inverted on objectB
    object1->OnContactStarted(object0, -vec3(normal.x(), normal.y(), normal.z()));
}

void Game2ContactEndedCallback(btPersistentManifold* const& manifold)
{
    int a = 0;
}

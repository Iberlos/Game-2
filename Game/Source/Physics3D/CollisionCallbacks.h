#pragma once

//Collision Callback stuff

bool Game2ContactAddedCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);
void Game2ContactStartedCallback(btPersistentManifold* const& manifold);
void Game2ContactEndedCallback(btPersistentManifold* const& manifold);
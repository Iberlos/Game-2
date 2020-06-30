#ifndef __MainGameScene_H__
#define __MainGameScene_H__

#include "Game/Scene.h"
#include "Game/ObjectPool.h"

class Game;
class GameObject;
class ResourceManager;

enum DificultyEnum
{
    DE_Easy = 0,
    DE_Medium,
    DE_Hard,
    DE_WelpBetterGiveUp
};

class MainGameScene : public Scene
{
    const unsigned int MAX_BULLETS_IN_POOL = 50;
    const unsigned int MAX_ENEMIES_IN_POOL = 10;
    unsigned int MAX_ENEMIES = 3;
    float ENEMY_SPAWN_DELAY = 2.0f;
    const float ENEMY_SPAWN_DISTANCE = 2.0f;

protected:
    //Used to stop the player from falling over
    //btHingeConstraint * m_PlayerConstraint;

    ObjectPool<GameObject*>* m_BulletPool;
    ObjectPool<GameObject*>* m_EnemyPool;

    float m_EnemySpawnTimer;
    DificultyEnum m_Dificulty;

public:
    MainGameScene(std::string a_Name, Game* pGame, ResourceManager* pResources, SoundPlayer* pPlayer);
    virtual ~MainGameScene();

    virtual void OnFocusOn() override;
    virtual void OnScenePopped() override { Reset(); }

    virtual void LoadContent() override;

    virtual bool OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void SetDificulty(DificultyEnum a_Dificulty);
    DificultyEnum GetDificulty() { return m_Dificulty; }

    //Bullet stuff
    void SpawnBullet(vec3 pos, vec3 rot, float distance, vec4 color);
    ObjectPool<GameObject*>* GetBulletPool() { return m_BulletPool; }
    void SpawnEnemy();
    ObjectPool<GameObject*>* GetEnemyPool() { return m_EnemyPool; }

};

#endif //__MainGameScene_H__

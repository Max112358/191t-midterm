// EnemyManager.h
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "_ModelLoaderMD2.h"
#include <vector>

class EnemyManager {
public:
    EnemyManager();
    virtual ~EnemyManager();

    void initEnemy(const char* modelPath);
    void spawnEnemy(float x, float y, float z);
    void updateEnemies();
    void drawEnemies();

private:
    std::vector<_ModelLoaderMD2*> enemies;
    const char* currentModelPath;
};

#endif

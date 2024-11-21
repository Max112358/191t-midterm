// EnemyManager.cpp
#include "EnemyManager.h"

EnemyManager::EnemyManager() {
    currentModelPath = nullptr;
}

EnemyManager::~EnemyManager() {
    for(auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

void EnemyManager::initEnemy(const char* modelPath) {
    currentModelPath = modelPath;
}

void EnemyManager::updateEnemies() {
    float deltaTime = 1.0f/60.0f; // Or calculate actual deltaTime

    for(auto enemy : enemies) {
        enemy->updateAnimation(deltaTime);
        enemy->setAnimationState(_ModelLoaderMD2::ANIM_RUN);
        enemy->dirAngleZ = 180; // Face left
        enemy->pos.x -= 0.1f;   // Move left
    }
}

void EnemyManager::spawnEnemy(float x, float y, float z) {
    if(!currentModelPath) return;

    _ModelLoaderMD2* enemy = new _ModelLoaderMD2();
    enemy->initModel(currentModelPath);
    enemy->pos.x = x;
    enemy->pos.y = y;
    enemy->pos.z = z;
    enemy->setAnimationState(_ModelLoaderMD2::ANIM_STAND);
    enemies.push_back(enemy);
}

void EnemyManager::drawEnemies() {
    for(auto enemy : enemies) {
        enemy->Draw();
    }
}

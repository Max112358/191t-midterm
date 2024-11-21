// EnemyManager.h
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "_ModelLoaderMD2.h"
#include "_Timer.h"
#include <vector>


class EnemyManager {
public:
    EnemyManager();
    virtual ~EnemyManager();

    void initEnemy(const char* modelPath);
    void spawnEnemy(float x, float y, float z);
    void updateEnemies();
    void drawEnemies();
    void checkSpawnTimer(); // New method to handle periodic spawning
    void removeOffscreenEnemies(); // New method to clean up enemies
    void checkCollisions(const _ModelLoaderMD2* player, bool isPlayerJumping);


    // New spawn configuration
    float spawnX = 400.0f;      // Spawn position just off right side
    float spawnY = -30.0f;        // Same height as player
    float spawnZ = -100.0f;     // Same Z-depth as player
    float enemySpeed = 4.5f;    // How fast enemies move left
    // Constants for collision detection
    const float ENEMY_WIDTH = 30.0f;  // Approximate width of enemy model
    const float PLAYER_WIDTH = 30.0f; // Approximate width of player model



private:
    std::vector<_ModelLoaderMD2*> enemies;
    const char* currentModelPath;
    float enemyScale;

    // Spawn timing
    _Timer* spawnTimer;
    int spawnInterval = 3000;    // Spawn every 3 seconds (in milliseconds)
    bool shouldSpawnEnemy();
    bool isColliding(const _ModelLoaderMD2* enemy, const _ModelLoaderMD2* player, bool isPlayerJumping);
    // Helper method to calculate distance between two points
    float getXDistance(const vec3& p1, const vec3& p2) {
        return std::abs(p2.x - p1.x);
    }

};

#endif

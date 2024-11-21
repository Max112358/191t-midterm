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
    const float ENEMY_WIDTH = 1.0f;  // Approximate width of enemy model
    const float PLAYER_WIDTH = 1.0f; // Approximate width of player model
    const float PLAYER_X_OFFSET = -120.0f; // Adjust this value to match visual position



private:
    std::vector<_ModelLoaderMD2*> enemies;
    const char* currentModelPath;
    float enemyScale;

    // Spawn timing
    _Timer* spawnTimer;
    int spawnInterval = 3000;    // Spawn every 3 seconds (in milliseconds)
    bool shouldSpawnEnemy();
    bool isColliding(const _ModelLoaderMD2* enemy, const _ModelLoaderMD2* player, bool isPlayerJumping);

    float getEdgeDistance(const _ModelLoaderMD2* enemy, const _ModelLoaderMD2* player) {
        float playerHalfWidth = (PLAYER_WIDTH * player->scale.x) / 2.0f;
        float enemyHalfWidth = (ENEMY_WIDTH * enemy->scale.x) / 2.0f;

        // Apply offset to player position for collision check
        float adjustedPlayerX = player->pos.x + PLAYER_X_OFFSET;

        float playerLeftEdge = adjustedPlayerX - playerHalfWidth;
        float playerRightEdge = adjustedPlayerX + playerHalfWidth;
        float enemyLeftEdge = enemy->pos.x - enemyHalfWidth;
        float enemyRightEdge = enemy->pos.x + enemyHalfWidth;

        if (playerRightEdge < enemyLeftEdge) {
            return enemyLeftEdge - playerRightEdge;
        }
        if (playerLeftEdge > enemyRightEdge) {
            return playerLeftEdge - enemyRightEdge;
        }
        return 0.0f;  // Edges are overlapping
    }

};

#endif

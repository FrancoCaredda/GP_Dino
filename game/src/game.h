#ifndef _GAME_H
#define _GAME_H

#define MAX_ENTITY_COUNT 25
#define STRING_BUFFER 256

#include "raylib.h"

typedef enum _EntityType
{
    PLAYER = 0,
    GROUND = 1,
    OBSTACLE = 2,

    MAX_ENTITY_TYPES
} EntityType;

typedef enum _EntityState
{
    IDLE = 0,
    JUMPING = 1,
    FALLING = 2,

    MAX_ENTITY_STATES
} EntityState;

typedef struct _Entity
{
    // Logic Related
    EntityType type;
    EntityState state;

    // Transform && Physics
    Vector2 position;
    Vector2 scale;
    Rectangle collider;

    // Rendering
    Texture2D* spriteSheet;
    Vector2 spriteCellSize;
    int sprite;

    // Animation
    int bAnimate;
    int animationFrames;
    float animationSpeed;
} Entity;


typedef enum _GameState
{
    PLAY = 0,
    OVER = 1,

    MAX_GAME_STATES
} GameState;

typedef struct _Game
{
    Entity entities[MAX_ENTITY_COUNT];
    Texture2D spriteSheets[MAX_ENTITY_TYPES];
    GameState state;

    int targetFPS;
} Game;

void InitGame(Game* game);
void UpdateGame(Game* game);
void DrawGame(Game* game);
void CloseGame(Game* game);

// Helper functions
void SetupEntities(Game* game);
void LoadSprite(Game* game, const char* spriteSheet, EntityType forEntity);
int CheckCollision(const Rectangle boundingBox1, const Rectangle boundingBox2);

#endif // !_GAME_H

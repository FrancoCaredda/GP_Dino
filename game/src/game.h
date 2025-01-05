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

typedef struct _Entity
{
    EntityType type;

    Vector2 position;
    Vector2 scale;
    Rectangle collider;

    Texture2D* spriteSheet;
    Vector2 spriteCellSize;
    int sprite;

    int bAnimate;
    int animationSpeed;
    int animationFrames;
} Entity;

typedef struct _Game
{
    Entity entities[MAX_ENTITY_COUNT];
    Texture2D spriteSheets[MAX_ENTITY_TYPES];

    int targetFPS;
} Game;

void InitGame(Game* game);
void UpdateGame(Game* game);
void DrawGame(Game* game);
void CloseGame(Game* game);

// Helper functions
void SetupEntities(Game* game);
void LoadSprite(Game* game, const char* spriteSheet, EntityType forEntity);

#endif // !_GAME_H

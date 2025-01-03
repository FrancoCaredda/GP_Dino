#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define STRING_BUFFER 256

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

    Texture2D* spriteSheet;
    Vector2 spriteCellSize;
    int sprite;

    int bAnimate;
} Entity;

#define MAX_ENTITY_COUNT 25
typedef struct _Game
{
    Entity entities[MAX_ENTITY_COUNT];
    Texture2D spriteSheets[MAX_ENTITY_TYPES];
} Game;

void LoadSprite(Game* game, const char* spriteSheet, EntityType forEntity)
{
    char textureToLoad[STRING_BUFFER] = ASSETS_DIRECTORY;
    strcat(textureToLoad, spriteSheet);
    game->spriteSheets[forEntity] = LoadTexture(textureToLoad);

    if (!IsTextureReady(game->spriteSheets[forEntity]))
        printf("%s texture isn't ready", spriteSheet);
}

void SetupEntities(Game* game)
{
    Entity entity = {
        .type = MAX_ENTITY_TYPES
    };

    for (int i = 0; i < MAX_ENTITY_COUNT; i++)
        game->entities[i] = entity;
}

void InitGame(Game* game)
{
    InitWindow(1920, 1080, "Google Dino Clone");
    SetTargetFPS(60);

    // Load Sprites
    LoadSprite(game, "/spritesheet_dino.png", PLAYER);
    LoadSprite(game, "/spritesheet_obstacles.png", OBSTACLE);
    LoadSprite(game, "/ground.png", GROUND);

    SetupEntities(game);

    game->entities[PLAYER] = (Entity){
        .type = PLAYER,
        .position = (Vector2){.x = 100, .y = 100 },
        .scale = (Vector2){.x = 2, .y = 2 },
        .sprite = 1,
        .spriteCellSize = (Vector2){.x = 58, .y = 43},
        .spriteSheet = &game->spriteSheets[PLAYER]
    };
}

void UpdateGame(Game* game)
{
    for (int i = 0; i < MAX_ENTITY_COUNT; i++)
    {
        switch (game->entities[i].type)
        {
        case PLAYER:
            // Do player's stuff
            continue;
        case OBSTACLE:
            // Do obstacle's stuff
            continue;
        default:
            continue;
        }
    }
}

void DrawGame(Game* game)
{
    BeginDrawing();

    Color color = { 255, 255, 255, 255 };
    ClearBackground(color);

    for (int i = 0; i < MAX_ENTITY_COUNT; i++)
    {
        Entity* entity = &game->entities[i];
        
        if (entity->type != MAX_ENTITY_TYPES)
        {
            Vector2 origin = {
                entity->spriteCellSize.x * (float)entity->sprite,
                entity->spriteCellSize.y
            };
            Rectangle source = {
                origin.x, origin.y,
                entity->spriteCellSize.x, entity->spriteCellSize.y
            };
            Rectangle destination = {
                0,
                0,
                entity->spriteCellSize.x * entity->scale.x,
                entity->spriteCellSize.y * entity->scale.y
            };

            Vector2 finalTransform = { -entity->position.x, -entity->position.y };
            DrawTexturePro(*entity->spriteSheet, source, destination,
                finalTransform, 0, RAYWHITE);
        }
    }

    EndDrawing();
}

void Update(Game* game)
{
    while (!WindowShouldClose())
    {
        UpdateGame(game);
        DrawGame(game);
    }
}

void CloseGame(Game* game)
{
    for (int i = 0; i < MAX_ENTITY_TYPES; i++)
        UnloadTexture(game->spriteSheets[i]);

    CloseWindow();
}

int main(int argc, char** argv)
{
    Game game;

    InitGame(&game);
    Update(&game);
    CloseGame(&game);

    return 0;
}
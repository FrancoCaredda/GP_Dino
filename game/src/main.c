#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

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
    int animationSpeed;
    int animationFrames;
} Entity;

#define MAX_ENTITY_COUNT 25
typedef struct _Game
{
    Entity entities[MAX_ENTITY_COUNT];
    Texture2D spriteSheets[MAX_ENTITY_TYPES];

    int targetFPS;
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

    game->targetFPS = 60;

    // Load Sprites
    LoadSprite(game, "/spritesheet_dino.png", PLAYER);
    LoadSprite(game, "/spritesheet_obstacles.png", OBSTACLE);
    LoadSprite(game, "/ground.png", GROUND);

    // Create entities
    SetupEntities(game);

    game->entities[PLAYER] = (Entity){
        .type = PLAYER,
        .position = (Vector2){.x = 0, .y = 100 },
        .scale = (Vector2){.x = 2, .y = 2 },
        .sprite = 1,
        .spriteCellSize = (Vector2){.x = 58, .y = 43},
        .spriteSheet = &game->spriteSheets[PLAYER],

        .bAnimate = 1,
        .animationSpeed = 5,
        .animationFrames = 8
    };

    for (int i = 0; i < 5; i++)
    {
        Entity entity = {
            .type = GROUND,
            .position = (Vector2){.x = 121 * 5 * i, .y = 186 },
            .scale = (Vector2){.x = 5, .y = 5 },
            .sprite = 0,
            .spriteCellSize = (Vector2){.x = 121, .y = 11},
            .spriteSheet = &game->spriteSheets[GROUND],
        };

        game->entities[PLAYER + i + 1] = entity;
    }
}

void UpdateGame(Game* game, double deltaTime)
{
    static int s_FramesCount = 0;
    for (int i = 0; i < MAX_ENTITY_COUNT; i++)
    {
        Entity* entity = &game->entities[i];

        // Animate entities
        if (entity->bAnimate && 
            entity->type != MAX_ENTITY_TYPES)
        {
            s_FramesCount++;
            s_FramesCount = s_FramesCount % game->targetFPS;

            entity->sprite = (int)(s_FramesCount * deltaTime * entity->animationSpeed) % entity->animationFrames;
        }

        // Entities' logic
        switch (entity->type)
        {
        case PLAYER:
            // Do player's stuff
            continue;
        case OBSTACLE:
            // Do obstacle's stuff
            continue;
        case GROUND:
            entity->position.x = entity->position.x - 100 * deltaTime;

            if (entity->position.x < -(entity->spriteCellSize.x * entity->scale.x + 1))
                entity->position.x = 2420;

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
    clock_t lastFrameTime = clock();
    while (!WindowShouldClose())
    {
        // Calculate delta time
        clock_t currentFrameTime = clock();
        double deltaTime = (double)(currentFrameTime - lastFrameTime) / CLOCKS_PER_SEC;
        lastFrameTime = currentFrameTime;

        UpdateGame(game, deltaTime);
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
#include "game.h"

#include <string.h>
#include <time.h>

// Entity related functions
static void AnimateEntity(Entity* entity, double deltaTime, int targetFPS)
{
    static int s_FramesCount = 0;

    // Animate entities
    if (entity->bAnimate &&
        entity->type != MAX_ENTITY_TYPES)
    {
        s_FramesCount++;
        s_FramesCount = s_FramesCount % targetFPS;

        entity->sprite = (int)(s_FramesCount * deltaTime * entity->animationSpeed) % entity->animationFrames;
    }

}

static void UpdateGround(Game* game, Entity* entity, double deltaTime)
{
    Entity* player = &game->entities[PLAYER];
    entity->position.x = entity->position.x - player->animationSpeed * deltaTime;

    if (entity->position.x < -(entity->spriteCellSize.x * entity->scale.x))
        entity->position.x = 2420;
}

static void UpdateGameLogic(Game* game, double deltaTime)
{

    for (int i = 0; i < MAX_ENTITY_COUNT; i++)
    {
        Entity* entity = &game->entities[i];
        AnimateEntity(entity, deltaTime, game->targetFPS);

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
            UpdateGround(game, entity, deltaTime);
            continue;
        default:
            continue;
        }
    }
}

// Game related functions
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
        .sprite = 0,
        .spriteCellSize = (Vector2){.x = 58, .y = 43},
        .spriteSheet = &game->spriteSheets[PLAYER],

        .bAnimate = 1,
        .animationSpeed = 5,
        .animationFrames = 6
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

void UpdateColliders(Game* game)
{
    for (int i = 0; i < MAX_ENTITY_COUNT; i++)
    {
        Entity* entity = &game->entities[i];
        entity->collider = (Rectangle){
            .x = entity->position.x,
            .y = entity->position.y,
            .width = entity->spriteCellSize.x * entity->scale.x,
            .height = entity->spriteCellSize.y * entity->scale.y
        };
    }
}

void DrawGame(Game* game)
{
    BeginDrawing();

    Color clearColor = { 255, 255, 255, 255 };
    Color colliderColor = { 255, 0, 0, 255 };
    ClearBackground(clearColor);

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
            DrawRectangleLines(entity->collider.x, entity->collider.y, entity->collider.width, entity->collider.height, colliderColor);
        }
    }

    EndDrawing();
}

void UpdateGame(Game* game)
{
    clock_t lastFrameTime = clock();
    while (!WindowShouldClose())
    {
        // Calculate delta time
        clock_t currentFrameTime = clock();
        double deltaTime = (double)(currentFrameTime - lastFrameTime) / CLOCKS_PER_SEC;
        lastFrameTime = currentFrameTime;

        UpdateColliders(game);
        UpdateGameLogic(game, deltaTime);
        DrawGame(game);
    }
}

void CloseGame(Game* game)
{
    for (int i = 0; i < MAX_ENTITY_TYPES; i++)
        UnloadTexture(game->spriteSheets[i]);

    CloseWindow();
}

// Helper functions
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
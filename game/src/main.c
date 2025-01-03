#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum _EntityType
{
    Player = 0,
    Ground = 1,
    Obstacle = 2,

    MaxEntityTypes
} EntityType;

typedef struct _Entity
{
    EntityType type;

    Vector2 position;
    Vector2 scale;

    Texture2D spriteSheet;
    Vector2 spriteCellSize;
    int sprite;

    int bAnimate;
} Entity;

#define MAX_ENTITY_COUNT 25
#define MAX_TEXTURE_COUNT 3
typedef struct _Game
{
    Entity entities[MAX_ENTITY_COUNT];
    Texture2D spriteSheets[MAX_TEXTURE_COUNT];
} Game;

void init(Game* game)
{
    InitWindow(1920, 1080, "Google Dino Clone");
    SetTargetFPS(60);
}

void update_game(Game* game)
{
    for (int i = 0; i < MAX_ENTITY_COUNT; i++)
    {
        switch (game->entities[i].type)
        {
        case Player:
            // Do player's stuff
            continue;
        case Obstacle:
            // Do obstacle's stuff
            continue;
        default:
            continue;
        }
    }
}

void draw_game(Game* game)
{
    BeginDrawing();

    Color color = { 0, 0, 0, 0 };
    ClearBackground(color);

    EndDrawing();
}

void update(Game* game)
{
    while (!WindowShouldClose())
    {
        update_game(game);
        draw_game(game);
    }
}

void close(Game* game)
{
    CloseWindow();
}

int main(int argc, char** argv)
{
    Game game;

    init(&game);
    update(&game);
    close(&game);

    return 0;
}
#include "game.h"

int main(int argc, char** argv)
{
    Game game;

    InitGame(&game);
    UpdateGame(&game);
    CloseGame(&game);

    return 0;
}
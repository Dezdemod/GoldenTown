#include <game.h>


int main(void)
{
    InitWindow(1280, 720, "Golden Town");
    InitAudioDevice();
    SetTargetFPS(60);
    Image windowIcon = LoadImage("collectibles/gold.png");
    SetWindowIcon(windowIcon);

    Game game;
    game.start();

    UnloadImage(windowIcon);

    return 0;
}
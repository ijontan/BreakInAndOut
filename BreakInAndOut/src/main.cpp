
#include "raylib.h"
#include "../include/Scene.hpp"

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Break In & Out");

    SetTargetFPS(60);

	Scene *scene = new Scene();
    while (!WindowShouldClose())
        scene->render();
    delete scene;

    CloseWindow();
    return 0;
}
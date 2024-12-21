#include "raylib.h"
#include "raymath.h"

int main()
{
    // Initialization
    const int screenDimensions[] = {384, 384};

    InitWindow(screenDimensions[0], screenDimensions[1], "Clash");
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    // Vector2 playerPosition = {0, 0};
    Vector2 mapPosition = {0, 0};

    float playerSpeed = 4.0f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 direction{};

        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        if (Vector2Length(direction) != 0)
        {
            // We normalize because we don't want to move faster diagonally (1.414)
            mapPosition = Vector2Subtract(mapPosition, Vector2Scale(Vector2Normalize(direction), playerSpeed));
        }

        DrawTextureEx(map, mapPosition, 0, 4, WHITE);



        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();        // Close window and OpenGL context
}
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

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPosition = {
        // Center the knight in the screen, and scale it by 4
        (float)screenDimensions[0]/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f), 
        (float)screenDimensions[1]/2.0f - 4.0f * (0.5f * (float)knight.height)
    };



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

        // Draw the map
        DrawTextureEx(map, mapPosition, 0, 4, WHITE);

        // Draw the knight
        Rectangle sourceRec = {0.0f, 0.0f, (float)knight.width/6.0f, (float)knight.height};
        // The x and y are the location we want to draw the knight in the window
        Rectangle destRec = {knightPosition.x, knightPosition.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};

        DrawTexturePro(knight, sourceRec, destRec, Vector2{}, 0.0f, WHITE);

        
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();        // Close window and OpenGL context
}
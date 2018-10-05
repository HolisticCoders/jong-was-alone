/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "character.cpp"
#include "checker.cpp"


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Jong was alone.");
    SetTargetFPS(60);
    ToggleFullscreen();
    //--------------------------------------------------------------------------------------
    
    Character jong;
    Checker checker;
    Camera2D camera;

    // Initialize the camera with default values.
    // Target the player position.
    camera.target = jong.position();
    camera.offset = (Vector2) {0, 0};
    camera.rotation = .0f;
    camera.zoom = 1.0f;

    jong.setCamera(&camera);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_LEFT))
            jong.go_left();
        if (IsKeyDown(KEY_RIGHT))
            jong.go_right();
        if (IsKeyPressed(KEY_SPACE))
            jong.jump();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(camera);

                checker.update();
                jong.update();

            EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

#include <stdio.h>
#include "chip8.h"
#include "raylib.h"
#include "draw.h"

int main()
{

    Chip8 chip;
    chip.stack_ptr = 0;
    chip8_init(&chip);
    load_rom("corax.ch8", &chip);

    InitWindow(64 * 10, 32 * 10, "CHIP-8");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        for (int z = 0; z < 10; z++)
        {
            // have to run this for 60Hz -> 60 x 10 is 600 instructions per seconds
            chip8_cycle(&chip);
        }

        // DrawText("Hello From chip8!", 247, 150, 20, GREEN);

        BeginDrawing();

        draw_screen(&chip);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

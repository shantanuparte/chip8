#include <stdio.h>
#include "chip8.h"
#include "raylib.h"
#include "draw.h"

int main()
{

    Chip8 chip;
    chip.stack_ptr = 0;
    chip8_init(&chip);
    load_rom("Airplane.ch8", &chip);

    InitWindow(64 * 10, 32 * 10, "CHIP-8");
    InitAudioDevice();
    Sound beep = LoadSound("beep.wav");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        update_keypad(&chip);
        for (int z = 0; z < 10; z++)
        {
            // have to run this for 60Hz -> 60 x 10 is 600 instructions per seconds
            chip8_cycle(&chip);
        }

        if (chip.timer > 0)
            chip.timer--;
        if (chip.sound > 0)
            chip.sound--;

        BeginDrawing();
        draw_screen(&chip);
        if (chip.sound > 0 && !IsSoundPlaying(beep))
            PlaySound(beep);
        if (chip.sound == 0 && IsSoundPlaying(beep))
            StopSound(beep);

        EndDrawing();
    }

    UnloadSound(beep);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

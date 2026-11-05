#include "draw.h"
#include "chip8.h"
#include "raylib.h"

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define MULTIPLIYER 10

void draw_screen(Chip8 *chip)
{

    ClearBackground(BLACK);

    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            if (chip->display[y * SCREEN_WIDTH + x])
                DrawRectangle(x * MULTIPLIYER, y * MULTIPLIYER, MULTIPLIYER, MULTIPLIYER, GREEN);
        }
    }
}



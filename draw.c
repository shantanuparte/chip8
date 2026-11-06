#include "draw.h"
#include "chip8.h"
#include "raylib.h"
#include <stdbool.h>

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

// Chip-8           keyboard
// 1 2 3 C           1 2 3 4
// 4 5 6 D           Q W E R
// 7 8 9 E           A S D F
// A 0 B F           Z X C V

void update_keypad(Chip8 *chip){

    chip->keypad[0x1] = IsKeyDown(KEY_ONE);
    chip->keypad[0x2] = IsKeyDown(KEY_TWO);
    chip->keypad[0x3] = IsKeyDown(KEY_THREE);
    chip->keypad[0xC] = IsKeyDown(KEY_FOUR);

    chip->keypad[0x4] = IsKeyDown(KEY_Q);
    chip->keypad[0x5] = IsKeyDown(KEY_W);
    chip->keypad[0x6] = IsKeyDown(KEY_E);
    chip->keypad[0xD] = IsKeyDown(KEY_R);

    chip->keypad[0x7] = IsKeyDown(KEY_A);
    chip->keypad[0x8] = IsKeyDown(KEY_S);
    chip->keypad[0x9] = IsKeyDown(KEY_D);
    chip->keypad[0xE] = IsKeyDown(KEY_F);

    chip->keypad[0xA] = IsKeyDown(KEY_Z);
    chip->keypad[0x0] = IsKeyDown(KEY_X);
    chip->keypad[0xB] = IsKeyDown(KEY_C);
    chip->keypad[0xF] = IsKeyDown(KEY_V);
}

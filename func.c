#include <stdio.h>
#include <stdint.h>
#include "chip8.h"


//0xD000 -> draw sprite on screen
void draw_sprite_on_screen(Chip8 *chip, uint8_t x, uint8_t y, uint8_t n)
{
    uint8_t x_coord = chip->Vx[x];
    uint8_t y_coord = chip->Vx[y];

    // collision flag is F'th register
    chip->Vx[0xF] = 0; // clear collision flag

    for (int row = 0; row < n; row++)
    {
        if (y_coord + row >= SCREEN_HEIGHT)
            break; // clip at bottom edge

        uint8_t sprite_byte = chip->mem[chip->I + row]; // read from memory

        for (int y = 0; y < 8; y++)
        {
            if (x_coord + y >= SCREEN_WIDTH)
                break; // clip at right edge

            if (sprite_byte & (0x80 >> y)) // get the bit though biwise operation. if non zero do the operation
            {
                int index = (y_coord + row) * SCREEN_WIDTH + (x_coord + y);

                if (chip->display[index]) // pixel already on -> collision
                    chip->Vx[0xF] = 1;

                chip->display[index] ^= 1; //  XOR onto the display
            }
        }
    }

    chip->draw_flag = true;
}

//3xnnn -> 




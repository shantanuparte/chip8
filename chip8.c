#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "chip8.h"

#define START_ADDR 0x200 // 512

// symbol
// int-> instruction operation
// x,y->placeholder for register
// kk -> 2 hex digits->8bit values (immidaite byte value)
// n -> 4 bit number
//  nnn -> memory address ->12bits

// each instruction is 2byte long with 4 bits of each instruction with is
// opcode register value value

void load_rom(const char *file_pt, Chip8 *chip)
{
    // load file from 512 though doc says some start from 1536 but we'll see later

    FILE *rom_file = fopen(file_pt, "rb");
    if (!rom_file) // !file_ptr is more professional
    {
        printf("Error opning file\n");
        return;
    }

    // checkig size in shorter manner
    fseek(rom_file, 0, SEEK_END);
    long file_size = ftell(rom_file);
    rewind(rom_file); // gets the seeker to start

    if (file_size > (MEMORY_SIZE - START_ADDR))
    {
        printf("File is bigger than %d bits\n", (MEMORY_SIZE - START_ADDR));
        return;
    }

    fread(&chip->mem[START_ADDR], 1, file_size, rom_file);
    fclose(rom_file);
}

void chip8_init(Chip8 *chip)
{
    memset(chip, 0, sizeof(*chip)); // use *chip to deference or it'll size the pointer

    chip->pc = START_ADDR; // pc should start here
}

void chip8_cycle(Chip8 *chip)
{

    uint16_t opcode = ((chip->mem[chip->pc] << 8) | chip->mem[chip->pc + 1]); // vacant bits are 0
    chip->pc += 2;

    uint8_t x = ((opcode >> 8) & 0x0F); // each 0 adds 4 0's in end os hex
    uint8_t y = ((opcode >> 4) & 0x000F);
    uint8_t n = opcode & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    uint16_t nnn = opcode & 0x0FFF;

    switch (opcode & 0xF000)
    {
    case 0x0000:
        if (opcode == 0x00E0)
        {
            clear_scr(chip);
        }
        else
        {
            printf("Sorry darling i haven't implemented it yet\n");
        }
        break;

    case 0x1000:
        // 1nnn - JP addr
        // Jump to location nnn.set pc to nnn
        chip->pc = nnn;
        break;

    case 0x6000:
        //  6XNN (Vx[x] = nn).
        chip->Vx[x] = nn;
    case 0xA000: // 10nnn
        //  ANNN (I = nnn).
        chip->I = nnn;

    case 0x7000:
        // 7xkk - ADD Vx, byte
        // Set Vx = Vx + kk.
        chip->Vx[x] += nn;

    case 0xD000: 
    {
        uint8_t x_coord = chip->Vx[x] ;  
        uint8_t y_coord = chip->Vx[y] ;

        //collision flag is F'th register
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

                if (sprite_byte & (0x80 >> y)) //get the bit though biwise operation
                {
                    int index = (y_coord + row) * SCREEN_WIDTH + (x_coord + y);

                    if (chip->display[index]) // pixel already on -> collision
                        chip->Vx[0xF] = 1;

                    chip->display[index] ^= 1; //  XOR onto the display
                }
            }
        }

        chip->draw_flag = true;
        break;
    }

    default:
        break;
    }
}

// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.

// The interpreter reads n bytes from memory, starting at the address stored in I.
// These bytes are then displayed as sprites on screen at coordinates (Vx, Vy).
// Sprites are XORed onto the existing screen.
// If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0.
// If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen.
// See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.

//  DXYN, last. It’s the hardest, and nothing appears on screen until it’s done.

void clear_scr(Chip8 *chip)
{
    memset(chip->display, 0, sizeof(chip->display));
    chip->draw_flag = true;
}

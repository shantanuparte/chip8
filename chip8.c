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
    uint8_t y = ((opcode >> 4) & 0x00F0);
    uint8_t n = opcode & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    uint16_t nnn = opcode & 0x0FFF;

    switch (opcode & 0xF000)
    {
    case 0:
        if (condition)
        {
            /* code */
        }

        break;

    default:
        break;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "chip8.h"
#include "func.h"

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
        break;

    case 0x1000:
        // 1nnn - JP addr
        // Jump to location nnn.set pc to nnn
        chip->pc = nnn;
        break;

    case 0x3000:
        // x, nn
        if (chip->Vx[x] == nn)
        {
            chip->pc += 2; // each itration is of 2
        }
        break;

    case 0x4000:
        // 4xkk
        if (chip->Vx[x] != nn)
        {
            chip->pc += 2;
        }
        break;

    case 0x5000:
        // 5xy0
        if (chip->Vx[x] == chip->Vx[y])
        {
            chip->pc += 2;
        }
        break;
    case 0x6000:
        //  6XNN (Vx[x] = nn).
        chip->Vx[x] = nn;
        break;
    case 0x7000:
        // 7xkk - ADD Vx, byte
        // Set Vx = Vx + kk.
        chip->Vx[x] += nn;
        break;

    case 0x9000:
        if (chip->Vx[x] != chip->Vx[y])
        {
            chip->pc += 2;
        }
        break;
    case 0xA000: // 10nnn
        //  ANNN (I = nnn).
        chip->I = nnn;
        break;

    case 0xD000:
        draw_sprite_on_screen(chip, x, y, n);
        break;

    default:
        break;
    }
}

void clear_scr(Chip8 *chip)
{
    memset(chip->display, 0, sizeof(chip->display));
    chip->draw_flag = true;
}


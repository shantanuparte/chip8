#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include "chip8.h"

#define START_ADDR 0x200 // 512
#define FONT_START 0x050

// symbol
// int-> instruction operation
// x,y->placeholder for register
// kk -> 2 hex digits->8bit values (immidaite byte value)
// n -> 4 bit number
//  nnn -> memory address ->12bits

// each instruction is 2byte long with 4 bits of each instruction with is
// opcode register value value

static const uint8_t fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void load_rom(const char *file_pt, Chip8 *chip)
{
    // load file from 512 though doc says some start from 1536 but we'll see later

    FILE *rom_file = fopen(file_pt, "rb");
    if (!rom_file) // !file_ptr is more professional
    {
        printf("Error opning file\n");
        fclose(rom_file);
        return;
    }

    // checkig size in shorter manner
    fseek(rom_file, 0, SEEK_END);
    long file_size = ftell(rom_file);
    rewind(rom_file); // gets the seeker to start

    if (file_size > (MEMORY_SIZE - START_ADDR))
    {
        printf("File is bigger than %d bits\n", (MEMORY_SIZE - START_ADDR));
        fclose(rom_file);
        return;
    }

    fread(&chip->mem[START_ADDR], 1, file_size, rom_file);
    fclose(rom_file);
}

void chip8_init(Chip8 *chip)
{
    memset(chip, 0, sizeof(*chip));                           // use *chip to deference or it'll size the pointer
    memcpy(&chip->mem[FONT_START], fontset, sizeof(fontset)); // copy to the memory address
    srand(time(NULL));
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
            // 00EE
            chip->stack_ptr--;
            chip->pc = chip->stack[chip->stack_ptr];
        }
        break;

    case 0x1000:
        // 1nnn - JP addr
        // Jump to location nnn.set pc to nnn
        chip->pc = nnn;
        break;

    case 0x2000:
        // 2nnn->
        chip->stack[chip->stack_ptr] = chip->pc;
        chip->stack_ptr++;
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

    case 0x8000:
    {
        uint8_t vx = chip->Vx[x];
        uint8_t vy = chip->Vx[y];

        switch (n)
        {
        case 0x0:
            chip->Vx[x] = vy;
            break;
        case 0x1:
            chip->Vx[x] = vx | vy;
            break;
        case 0x2:
            chip->Vx[x] = vx & vy;
            break;
        case 0x3:
            chip->Vx[x] = vx ^ vy;
            break;
        case 0x4:
        {
            uint16_t sum = vx + vy;
            chip->Vx[x] = sum & 0xFF;
            chip->Vx[0xF] = (sum > 255);
            break;
        }
        case 0x5:
            chip->Vx[x] = vx - vy;
            chip->Vx[0xF] = (vx >= vy);
            break;
        case 0x6:
            chip->Vx[x] = vx >> 1;
            chip->Vx[0xF] = vx & 0x01;
            break;
        case 0x7:
            chip->Vx[x] = vy - vx;
            chip->Vx[0xF] = (vy >= vx);
            break;
        case 0xE:
            chip->Vx[x] = vx << 1;
            chip->Vx[0xF] = (vx >> 7) & 0x01;
            break;
        default:
            break;
        }
        break;
    }

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
    case 0xB000:
        chip->pc = (nnn + chip->Vx[0]);
        break;
    case 0xC000:
        chip->Vx[x] = (rand() & 255) & nn;
        break;
    case 0xD000:
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
    break;
    case 0xE000:
        if (nn == 0x9E)
        {
            if (chip->keypad[chip->Vx[x]])
            {
                chip->pc += 2;
            }
        }
        else if (nn == 0xA1)
        {
            if (!(chip->keypad[chip->Vx[x]]))
            {
                chip->pc += 2;
            }
        }

        break;
    case 0xF000:
        switch (nn)
        {
        case 0x0A:
            // wait till which key is pressed

            bool is_presed = false;
            for (int i = 0; i < 16; i++)
            {
                if (chip->keypad[i])
                {
                    chip->Vx[x] = i;
                    is_presed = true;
                    break;
                }
            }
            if (!is_presed)
            {
                chip->pc -= 2;
            }

            break;
        case 0x1E:
            chip->I += chip->Vx[x];
            break;
        case 0x29:
            chip->I = FONT_START + (chip->Vx[x] * 5);
            break;
        case 0x33:
            uint8_t num = chip->Vx[x];
            for (int i = 2; i >= 0; i--)
            {
                chip->mem[chip->I + i] = num % 10;
                num /= 10;
            }
            break;
        case 0x55:
            for (int i = 0; i <= x; i++) // equal cause till Vx
            {
                chip->mem[chip->I + i] = chip->Vx[i];
            }

            break;
        case 0x65:
            for (int i = 0; i <= x; i++)
            {
                chip->Vx[i] = chip->mem[chip->I + i];
            }
            break;
        case 0x07:
            chip->Vx[x] = chip->timer;
            break;
        case 0x15:
            chip->timer = chip->Vx[x];
            break;
        case 0x18:
            chip->sound = chip->Vx[x];
            break;
        default:
            break;
        }
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






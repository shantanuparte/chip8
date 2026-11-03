#include <stdio.h>
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

    if (get_file_size(file_pt) > (MEMORY_SIZE - START_ADDR))
    {
        printf("File is bigger than %d bits\n", (MEMORY_SIZE - START_ADDR));
        return;
    }

    //we read 2 bytes idk how

}

long get_file_size(const char *file_pt)
{

    FILE *file = fopen(file_pt, "rb");

    if (file != NULL)
    {
        printf("Error opening file\n");
        return -1;
    }
    long int offset = 0;

    if (fseek(file_pt, offset, SEEK_END) != -1) // move seeker to last
    {
        printf("Error in mving file pointer");
        return -1;
    }

    long size_of_file = ftell(file_pt);

    return size_of_file;
}

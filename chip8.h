#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdio.h>

#define MEMORY_SIZE 4096
#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

typedef struct
{
    uint8_t mem[MEMORY_SIZE]; // from location 0x000 (0) to 0xFFF (4095).
    uint8_t Vx[16];           // 16 general purpose reg's->x placeholder for 0 to F(15) in hex16

    // pesudo registers
    uint16_t I;  // Index register used to store memory address
    uint16_t pc; // program counter used to store currectly execution address

    uint16_t stack[16]; // used to store the address that the interpreter shoud return when subroutine is finised wtf?
    uint8_t stack_ptr;  // stack pointer->topmost level of stack

    // two special registers->
    uint8_t timer;
    uint8_t sound;

    // raylib to display later
    uint8_t display[SCREEN_HEIGHT * SCREEN_WIDTH]; // size of screen total 1984: two states 1-> on, 0-> off
    uint8_t keypad[16];
    bool draw_flag;

} Chip8;

void chip8_init(Chip8 *chip);
void load_rom(const char *file_pt, Chip8 *chip); // use const char * instead of FILE *. as it more safe in some way
void chip8_cycle(Chip8 *chip);
void clear_scr(Chip8 *chip);

#endif

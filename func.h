#ifndef FUNC_H
#define FUNC_H

#include "chip8.h"


//0xD000 -> draw sprite on screen
void draw_sprite_on_screen(Chip8 *chip, uint8_t x, uint8_t y, uint8_t n);

#endif
#ifndef DRAW_H
#define DRAW_H

#include "raylib.h"
#include "chip8.h"

void draw_screen(Chip8 *chip);
void update_keypad(Chip8 *chip);

#endif
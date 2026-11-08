# Chip 8 emulator

It is a cli based Chip 8 Emulator. Just pass the file path and get it working

![Demo](chip.gif)

# Features

- Supports all machine codes of base chip-8 emulator
- easy to use

## Installations

Only runs on linux, ૮(•͈⌔•͈)ა
I have the beep.wav in the src for code to use. so the sound doens't get in game. 

Install binary directly [Dowdload for Linux](https://github.com/shantanuparte/chip8/releases/download/v1.0.0/chip8)


## Usage

Change permission

```
chmod +x chip8
```

And run the binary

```
./chip8 /path/to/chip8_file.chip8
```

## Build from source (CMake)

I have added a Airplane.ch8 game if you want to play

Clone the repository:

```
git clone https://github.com/shantanuparte/chip8.git
cd chip8
```

Configure the project:

```
cmake -S . -B build
```

Build:

```
cmake --build build
```

Run the emulator:

```
./build/chip8 /path/to/chip8_file.chip8
```

## Project structure

| File                | What it does                      |
| ------------------- | --------------------------------- |
| `main.c`            | Main loop and retriving funcitons |
| `chip8.c / chip8.h` | The core instructions and logic   |
| `draw.c / draw.h`   | raylib draw window                |

## License

I am using the MIT License for this project (¬‿¬)

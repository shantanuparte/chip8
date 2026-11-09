# Chip 8 emulator

It is a cli based Chip 8 Emulator. Just pass the file path and get it working

![Demo](chip.gif)

# Features

- Supports all machine codes of base chip-8 emulator
- easy to use

## Installation

Download `chip8` from the
[latest release](https://github.com/shantanuparte/chip8/releases/latest)
and `beep.wav` and `Airplane.ch8` from
[git repo](https://github.com/shantanuparte/chip8.git)
and put all three in the same folder.

```
chmod +x chip8
./chip8 Airplane.ch8
```

Linux only. The binary has raylib built in, so you don't need to install it.

## Usage

Change permission

```
chmod +x chip8
```

And run the binary

```
./chip8 /path/to/chip8_file.ch8
```

## Build from source (CMake)

Fedora:

```
sudo dnf install gcc cmake git mesa-libGL-devel libX11-devel libXrandr-devel \
libXi-devel libXcursor-devel libXinerama-devel alsa-lib-devel
```

Debian/Ubuntu:

```
sudo apt install build-essential cmake git libgl1-mesa-dev libx11-dev \
libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libasound2-dev
```

Arch:

```
sudo pacman -S base-devel cmake git mesa libx11 libxrandr libxi libxcursor libxinerama alsa-lib
```

```
cmake -B build && cmake --build build
./build/chip8 roms/Airplane.ch8
```

## Prebuilt binary

Keep `beep.wav` and `Airplane.ch8`in the same folder as `chip8` and run it from that folder:
`./chip8 Airplane.ch8`

## Controls

CHIP-8 keypad `1 2 3 C / 4 5 6 D / 7 8 9 E / A 0 B F` maps to
`1 2 3 4 / Q W E R / A S D F / Z X C V`.

## Project structure

| File                | What it does                      |
| ------------------- | --------------------------------- |
| `main.c`            | Main loop and retriving funcitons |
| `chip8.c / chip8.h` | The core instructions and logic   |
| `draw.c / draw.h`   | raylib draw window                |

## License

I am using the MIT License for this project (¬‿¬)

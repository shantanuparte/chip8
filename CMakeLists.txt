cmake_minimum_required(VERSION 3.14)
project(chip8 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Allow older sub-projects to configure under CMake 4.x
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Always build raylib statically so the binary has no runtime raylib dependency
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable(chip8 src/main.c src/chip8.c src/draw.c)
target_compile_options(chip8 PRIVATE -Wall -Wextra)
target_link_libraries(chip8 PRIVATE raylib m)

add_custom_command(TARGET chip8 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/beep.wav
        $<TARGET_FILE_DIR:chip8>/beep.wav)
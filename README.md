# SDL2_OPENGL_BOILERPLATE
### by [Mattéo Leclercq](https://github.com/MatteoL-W/)

## Dependencies description

This boilerplate contains SDL2, SDL2_image, SDL2_TTF, SDL2_Mixer, GLM

It should be working on Linux and Windows (_MinGW_)

If you want to build with **another compiler than MinGW (_MSVC_)**, you shouldn't download my sdl2_dependencies submodule but do the same manipulation with the SDL2 libs for VC that you can download on [libsdl.org](https://www.libsdl.org/).

Here is an example with SDL2_Mixer : [https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-VC.zip](https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-VC.zip)

🚩 **Warning**: For Windows (MinGW), only includes files are handled by the CMake. It means that you'll need to install SDL2 libs in your MinGW Compiler. If it's not a problem for you, the instructions are below.

## Default framework explanation

### 🚀 WIP ~

## Prerequisite (both Linux & Windows)

- Install [CMAKE](https://cmake.org/download/)
- Checkout `src/Configuration` folder to custom your project

## Installation
### Linux
- Install those libs ```sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev```
- Install the repository as a template and install **aminosbh's submodule for SDL2** : `git submodule update -i -r cmake/sdl2`

### Windows
- Install the repository as a template and install **SDL2 dependencies** : `git submodule update -i -r lib/sdl2_dependencies`
- If your computer is in 32bits (🤔), for each libs, you'll need to copy the `i686-w64-mingw32/lib/` and `i686-w64-mingw32/bin/` content into your `C:/MinGW/lib` folder. Else, you can do the same manipulation with the `x86_64-w64-mingw32/lib/` folder. You shouldn't have to copy the `cmake/SDL2` content.

## Build
- At the repo root, execute ```cmake --build build```
- You can execute the window in ```./bin/```


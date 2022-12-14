#include <SDL2/SDL.h>

#include "Configuration/Frame.hpp"
#include "Engine.hpp"

Engine *engine = nullptr;
Engine *Engine::_instance;

int main(int argc, char *argv[]) {
    engine = Engine::GetInstance();

    while (engine->isRunning()) {
        Uint32 frameStart = SDL_GetTicks();

        engine->refresh();

        // FPS Handle (custom in main.h)
        unsigned int frameTime = SDL_GetTicks() - frameStart;
        if (Configuration::Frame::FRAME_DELAY > frameTime) {
            SDL_Delay(Configuration::Frame::FRAME_DELAY - frameTime);
        }
    }

    return 1;
}

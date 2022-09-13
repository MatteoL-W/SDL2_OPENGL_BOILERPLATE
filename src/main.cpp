#include <SDL2/SDL.h>

#include "main.h"
#include "Engine.h"

Engine *engine = nullptr;
Engine* Engine::_instance;

int main(int argc, char *argv[]) {
    engine = Engine::GetInstance();

    while (engine->isRunning()) {
        Uint32 frameStart = SDL_GetTicks();

        engine->refresh();

        // FPS Handle (custom in main.h)
        unsigned int frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 1;
}

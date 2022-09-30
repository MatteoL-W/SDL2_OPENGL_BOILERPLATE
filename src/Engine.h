#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <memory>

#include "State/IState.h"
#include "State/Menu/MenuState.h"

class Engine {
public:
    ~Engine() = default;

    // Singleton
    static Engine *GetInstance();
    static Engine* _instance;

    // State Machine
    std::shared_ptr<IState> getCurrentState() { return _currentState; };

    void refresh();
    void clean();

    [[nodiscard]] bool isRunning() const { return _isRunning; };

private:
    Engine();
    static void initiateWindowSize();

    // States
    std::shared_ptr<MenuState> _menuInterface;
    std::shared_ptr<IState> _currentState;

    SDL_Window *_window;
    SDL_GLContext _context;
    SDL_Event _event{};

    bool _isRunning = false;
};

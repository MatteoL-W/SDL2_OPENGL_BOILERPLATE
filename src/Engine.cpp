#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "Engine.hpp"
#include "State/Menu/MenuState.hpp"
#include "Tool/Initializer/Initializer.hpp"
#include "Configuration/Window.hpp"
#include "Configuration/Project.hpp"

/**
 * @brief Initialize the engine (assign the window and opengl, define the engine as running)
 */
Engine::Engine() {
    Tool::Initializer::initialize();

    _window = SDL_CreateWindow(
        Configuration::Project::Title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Configuration::Window::WIDTH,
        Configuration::Window::HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    Tool::Initializer::setOpenGLAttribute();
    _context = SDL_GL_CreateContext(_window);
    Tool::Initializer::verifyOpenGLContext(_context, _window);

    /* Define the states */
    _menuInterface = std::make_shared<MenuState>();

    /* Define the default interface */
    _currentState = _menuInterface;

    _isRunning = true;
    initiateWindowSize();
}

Engine *Engine::GetInstance() {
    if (_instance == nullptr) {
        _instance = new Engine{};
    }
    return _instance;
}

/**
 * @brief Quit the engine properly
 */
void Engine::clean() {
    _isRunning = false;
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

/**
 * @brief Chose the right interface and execute its method
 */
void Engine::refresh() {
    _currentState->update();

    glClear(GL_COLOR_BUFFER_BIT);
    _currentState->render();
    SDL_GL_SwapWindow(_window);

    _currentState->handleEvents(_event);
}

/**
 * @brief Initiate the window size and the orthonormal coordinate system
 */
void Engine::initiateWindowSize() {
    glViewport(0, 0, Configuration::Window::WIDTH, Configuration::Window::HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(
            0, Configuration::Window::WIDTH,
            0, Configuration::Window::HEIGHT
    );
}
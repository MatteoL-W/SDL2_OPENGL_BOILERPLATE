#pragma once

#include "State/IState.hpp"

class MenuState : public IState {
public:
    MenuState();

    void handleEvents(SDL_Event event) override;
    void update() override;
    void render() override;
};


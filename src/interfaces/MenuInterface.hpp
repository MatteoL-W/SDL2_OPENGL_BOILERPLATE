#pragma once

#include "Engine.hpp"
#include "interfaces/Interface.hpp"
#include "Menu/Menu.hpp"

class MenuInterface : public Interface {
public:
    explicit MenuInterface(Engine *game)
            : game(game), menu(new Menu()) {
    }

    ~MenuInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Engine *game;

    Menu *menu;

};

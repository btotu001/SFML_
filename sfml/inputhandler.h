#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"
#include "moveupcommand.h"
#include "movedowncommand.h"
#include "moverightcommand.h"
#include "moveleftcommand.h"

class InputHandler {

public:
    /*
    InputHandler(){
        buttonY_ = new MoveUpCommand();
        buttonX_ = new MoveLeftCommand();
        buttonA_ = new MoveDownCommand();
        buttonB_ = new MoveRightCommand();
    }
    */
    // Sets a new command for button
    // void setCommandForButton(Command* button, Command* command);
    InputHandler();
    Command* handleInput(sf::RenderWindow* pWindow, Game* pMyGame);

private:

    int JoystickID = -1;

    // All the possible controller inputs in the game
    Command* buttonX_;
    Command* buttonY_;
    Command* buttonA_;
    Command* buttonB_;


};
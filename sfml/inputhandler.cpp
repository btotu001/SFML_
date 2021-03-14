#include "inputhandler.h"

InputHandler::InputHandler() {
        //Assign the command poiinters
    
        buttonY_ = new MoveUpCommand();
        buttonX_ = new MoveLeftCommand();
        buttonA_ = new MoveDownCommand();
        buttonB_ = new MoveRightCommand();

        //Find a joystick...
        sf::Joystick::update();
        for(int i=0;i<31;i++){
            if (sf::Joystick::isConnected(i)) {
                this->JoystickID = i;
                std::cout << "Joystick " << JoystickID << " is connected! " << std::endl;
                std::cout << "It has " << sf::Joystick::getButtonCount(JoystickID);
                break;

            }
    }
}



Command* InputHandler::handleInput(sf::RenderWindow* pWindow,
                               Game* pMyGame){

        sf::Event event;
        while (pWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                pWindow->close();

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape)
                    pWindow->close();
            }
            // If W,A,S or D is pressed, give some force
            // to our ball 
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::W){
                    return buttonY_;
                    //pMyGame->BallUp();
                    //buttonY_->execute();
                }
                if (event.key.code == sf::Keyboard::A)
                    return buttonX_;
                    //pMyGame->BallLeft();
                if (event.key.code == sf::Keyboard::S)
                    return buttonA_;
                    //pMyGame->BallDown();
                if (event.key.code == sf::Keyboard::D)
                    return buttonB_;
                    //pMyGame->BallRight();      
            }
        } // end while

        if (JoystickID >= 0 && sf::Joystick::isConnected(JoystickID)) {
            for (int i = 0; i < 32; i++) {
                if (sf::Joystick::isButtonPressed(JoystickID, i)) {
                    //std::cout << "Button " << i << " was presseed!" << std::endl;

                    //For PS4 controller 0,1,2,3 == X,A,B,Y
                    switch (i) {
                        case 0:
                            return buttonX_;
                        break;
                        case 1:
                            return buttonA_;
                        break;
                        case 2:
                            return buttonB_;
                        break;
                        case 3:
                            return buttonY_;
                        break;
                    }
                }
            }
        }

    return nullptr;
}

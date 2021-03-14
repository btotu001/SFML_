//#include "command.h"
#include <iostream>

class MoveRightCommand : public Command {

public:

    virtual void execute(Ball& ball) {
        // Todo: 
        // Move the "player" up
        Vector3 vel = ball.m_particle->getVelocity();
        vel = vel + Vector3(5.0, 0.0, 0.0);
        ball.m_particle->setVelocity(vel);
        std::cout << "EXECUTE RIGHT!!!" << std::endl;
        //jump(); 
    }
};
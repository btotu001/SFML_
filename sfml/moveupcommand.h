#include "command.h"
#include <iostream>

class MoveUpCommand : public Command {

public:

    virtual void execute(Ball& ball) {
        // Todo: 
        // Move the "player" up
        Vector3 vel = ball.m_particle->getVelocity();
        vel = vel + Vector3(0.0, 5.0, 0.0);
        ball.m_particle->setVelocity(vel);
        std::cout << "EXECUTE UP!!!" << std::endl;
        //jump(); 
    }
};
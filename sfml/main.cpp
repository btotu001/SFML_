#include <SFML/Graphics.hpp>
#include "game_constants.h"
#include "game.h"
#include "inputhandler.h"
#include "renderer.h"
#include <iostream>

int main(){

    // Create the window - acts as a render target!
    sf::RenderWindow window(sf::VideoMode(GameConstants::WinWidth, 
                                          GameConstants::WinHeight), "SFML works!");

    // Limit the frame rate    
    window.setFramerateLimit(60);

    // Let's construct our game-object
    Game myGame;
    //also construct a renderer object
    Renderer myRenderer;

    // Let's constuct an input handler
    InputHandler myInputHandler;

    // --------------------------------------------------------
    // The actual game loop related stuff starts somewhere around here...
    // --------------------------------------------------------

    // This is the time step for the physics simulation
    double delta = 0.001;

    sf::Clock clock;
    sf::Time elapsed_time = clock.restart();

    // Accumulates elapsed time and is reduced when updating the physics simulation
    double accumulator = 0.0; 

    // Get position from particle - used for interpolation later on...
    //Vector3 curr_pos = myGame.particle.getPosition(); 
    //Vector3 last_pos = curr_pos;

    // --------------------------------------------------------
    // The "game loop" starts right here! In SFML, it's standard practive to use
    // a while-loop like the one below.
    // --------------------------------------------------------
    while (window.isOpen()){

        elapsed_time = clock.getElapsedTime();
        double frametime = elapsed_time.asSeconds();
        clock.restart();
        
        accumulator += frametime;

        //
        // "Inputhandler" stuff first:
        //

        // Call our inputhandler's handleInput()-method
        Command* cmd = myInputHandler.handleInput(&window, &myGame);
        if (cmd != nullptr){
            cmd->execute(myGame.myBall);
        }

        //std::cout << elapsed_time.asMicroseconds() << std::endl;

        // --------------------------------------------------------
        // Game Logic Update here:
        // --------------------------------------------------------

        // Update our particle physics model
        while( accumulator >= delta ){
            myGame.update(delta);
            // last_pos = curr_pos;
            // curr_pos = myGame.particle.getPosition();
            accumulator -= delta;
        }

        // The remainder "in between simulation steps" - NOT USED NOW
        // const double alpha = accumulator / delta;

        // particle.printPosition(); // just for debug..

        // Interpolate the position for the particle - NOT USED NOW
        // Vector3 interp_pos = curr_pos*alpha + last_pos*(1-alpha);
        
        // set the position for our moving circle, but 
        // ONLY if it is above ground -  NOT USED NOW!
        /*  interpolate the particle's position
        if (curr_pos.getY() >= 0.0){
            moving_circle.setPosition(
                sf::Vector2f(interp_pos.getX(), 
                            GameConstants::WinHeight-interp_pos.getY()-grass.getSize().y));
        }
        */

       // ------------------------------------------------------------
       // Render the game to screen/window
       // ------------------------------------------------------------
       myRenderer.render(&window, &myGame);

    }

    return 0;
}

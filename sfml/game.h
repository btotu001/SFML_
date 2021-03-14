#pragma once
#include "gravityforce.h"
#include "ball.h"
#include "gameobject.h"
#include "airblower.h"
#include "blackholeforce.h"
#include "game_constants.h"
#include "collisiondetector.h"
#include <SFML/Graphics.hpp>
#include <list>

class Game {
public:

    Game();

    void update(double deltatime);
    //void render(sf::RenderWindow * rw);

    void BallUp();
    void BallLeft();
    void BallRight();
    void BallDown();

    // Member variables for the ball and particle
    Ball myBall;
    Ball* pMyBall;
    Particle particle;

    Box myBox;
    Particle box_particle;

    Box myBox2;
    Particle box_particle2;

    Box myBox3;
    Particle box_particle3;

    Box myBox4;
    Particle box_particle4;

    // Member variables for forces and the airblowers
    Airblower myBlower;
    Airblower myBlowerOther;
    GravityForce gf;
    AirblowerForce abf_first;
    AirblowerForce abf_other;
    BlackholeForce bhf;

private:
   
    

    // Lists for particles and balls  
    // -- THESE SHOULD BE CONVERTED INTO A COMMON GAMEOBJECT-LIST!!!
    std::list<Particle*> list_particles;
    std::list<Ball*> list_balls;

    //helper for bottomwall bounce
    void checkAndResolveBottomWall(Ball* b);
    void checkAndResolveRightWall(Ball* b);
    void checkAndResolveLeftWall(Ball* b);

};
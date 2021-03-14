#include "game.h"
#include <iostream>
#include "collisiondetector.h"
#include <SFML/System.hpp>

// Constructor
Game::Game(){
    //the ball particle
    particle.setPosition(Vector3(600.0, 100.0, 0.0));
    particle.setMass(0.5);
    particle.setVelocity(Vector3(0.0, 0.0, 0.0));

    myBall.setPhysicsParticle(&particle);
    myBall.setRadius(25.0);
    myBall.update(); //updatesthe bounding box

    //THe box particle - the position is the CENTER of the box
    box_particle.setPosition(Vector3(300.0, 400.0, 0.0));
    box_particle.setMass(100.0);
    //set our box-gameobject
    myBox.setPhysicsParticle(&box_particle);
    myBox.setWidth(200.0);
    myBox.setHeight(200.0);
    myBox.update();


    //THe box particle - the position is the CENTER of the box
    box_particle2.setPosition(Vector3(800.0, 800.0, 0.0));
    box_particle2.setMass(100.0);
    //set our box-gameobject
    myBox2.setPhysicsParticle(&box_particle2);
    myBox2.setWidth(4000.0);
    myBox2.setHeight(200.0);
    myBox2.update();

    //THe box particle - the position is the CENTER of the box
    box_particle3.setPosition(Vector3(1300.0, 400.0, 0.0));
    box_particle3.setMass(100.0);
    //set our box-gameobject
    myBox3.setPhysicsParticle(&box_particle3);
    myBox3.setWidth(200.0);
    myBox3.setHeight(200.0);
    myBox3.update();

    //THe box particle - the position is the CENTER of the box
    box_particle4.setPosition(Vector3(800.0, 400.0, 0.0));
    box_particle4.setMass(100.0);
    //set our box-gameobject
    myBox4.setPhysicsParticle(&box_particle4);
    myBox4.setWidth(600.0);
    myBox4.setHeight(20.0);
    myBox4.update();

    // Gravity-force
    //GravityForce gf(Vector3(0, -10.0, 0));  
    //gf.setGravity(Vector3(0, 0.0, 0));
    gf.setGravity(Vector3(0, -45.0, 0));
    //gf.setGravity(Vector3(0, -15.0, 0));

    // Airblower-forces
    //AirblowerForce abf_first(Vector3(500.0,400.0,0.0), Vector3(-50.0, 150.0, 0.0), 10.0, 100.0);
    abf_first.setPosition(Vector3(750.0,430.0,0.0));
    abf_first.setForce(Vector3(-500.0, 3500.0, 0.0));
    abf_first.setDist(10.0);
    abf_first.setHeight(100.0);
    //AirblowerForce abf_other(Vector3(950.0,200.0,0.0), Vector3(50.0, 150.0, 0.0), 10.0, 100.0);
    abf_other.setPosition(Vector3(750.0,20.0,0.0));
    abf_other.setForce(Vector3(500.0, 1500.0, 0.0));
    abf_other.setDist(10.0);
    abf_other.setHeight(100.0);

    // Airblower-related stuff
    myBlower.setAirblowerForce(&abf_first);
    myBlowerOther.setAirblowerForce(&abf_other);

    // Blackhole-force:
    bhf.setPosition(Vector3(760.0, 340.0, 0.0));
    bhf.setForce(7000.0);
    bhf.setRadius(300.0);


    //sf::sleep(sf::seconds(10.0));

    
}

void Game::checkAndResolveBottomWall(Ball* ball) {

    // Test a simple bounce effect... from ground
    if (ball->m_particle->getPosition().getY() - ball->getRadius() <= 0.0 &&
        ball->m_particle->getVelocity().getY() < 0.0) {
        Vector3 vel = ball->m_particle->getVelocity();
        double y = vel.getY();
        //vel = vel + Vector3(0.0, -2 * y, 0.0);
        vel = vel + Vector3(0.0, -y, 0.0); //dont bounce
        //vel = vel * damping;
        ball->m_particle->setVelocity(vel);
    }
}


void Game::checkAndResolveRightWall(Ball* ball) {

    // Test a simple bounce effect... from right-hand side wall
    if (ball->m_particle->getPosition().getX() + ball->getRadius() >= GameConstants::WinWidth &&
        ball->m_particle->getVelocity().getX() > 0.0) {
        Vector3 vel = ball->m_particle->getVelocity();
        double x = vel.getX();
        vel = vel + Vector3(-2.0 * x, 0.0, 0.0);
        //vel = vel * damping;
        ball->m_particle->setVelocity(vel);
    }

}


void Game::checkAndResolveLeftWall(Ball * ball) {

    // Test a simple bounce effect... from left-hand side wall
    if (ball->m_particle->getPosition().getX() - ball->getRadius() <= 0.0 &&
        ball->m_particle->getVelocity().getX() < 0.0) {
        Vector3 vel = ball->m_particle->getVelocity();
        double x = vel.getX();
        vel = vel + Vector3(-2.0 * x, 0.0, 0.0);
        //vel = vel * damping;
        ball->m_particle->setVelocity(vel);
    }

}


// Updates the game logic - including physics sim.
void Game::update(double deltatime){
    
    gf.updateForce(&particle, 0.0);
    abf_first.updateForce(&particle, 0.0);
    abf_other.updateForce(&particle, 0.0);
    bhf.updateForce(&particle,0.0);
    particle.update(deltatime);
    myBall.update();

    //pMyBall->update();
    
    myBox.update();
    myBox2.update();
    myBox3.update();
    myBox4.update();

    //check collisions against walls
    checkAndResolveBottomWall(&myBall);
    checkAndResolveRightWall(&myBall);
    checkAndResolveLeftWall(&myBall);

    /*
   

    */
        //collision detection against the box
        if (CollisionDetector::testAABBOverlap((&myBall), &myBox)) {
            //there might be a hit 
            
            //check closer...
            CollisionDetector::detectAndResolveCollision(&myBall, &myBox);
        }

        //collision detection against the box
        if (CollisionDetector::testAABBOverlap((&myBall), &myBox2)) {
            //there might be a hit 

            //check closer...
            CollisionDetector::detectAndResolveCollision(&myBall, &myBox2);
        }

        //collision detection against the box
        if (CollisionDetector::testAABBOverlap((&myBall), &myBox3)) {
            //there might be a hit 

            //check closer...
            CollisionDetector::detectAndResolveCollision(&myBall, &myBox3);
        }


        //collision detection against the box
        if (CollisionDetector::testAABBOverlap((&myBall), &myBox4)) {
            //there might be a hit 

            //check closer...
            CollisionDetector::detectAndResolveCollision(&myBall, &myBox4);
        }
        
  }




void Game::BallDown(){
    Vector3 vel = pMyBall->m_particle->getVelocity();
    vel = vel + Vector3(0.0, -5.0, 0.0);
    pMyBall->m_particle->setVelocity(vel);
}
void Game::BallUp(){
    Vector3 vel = pMyBall->m_particle->getVelocity();
    vel = vel + Vector3(0.0, 10.0, 0.0);
    pMyBall->m_particle->setVelocity(vel);
}
void Game::BallLeft(){
    Vector3 vel = pMyBall->m_particle->getVelocity();
    vel = vel + Vector3(-5.0, 0.0, 0.0);
    pMyBall->m_particle->setVelocity(vel);
}
void Game::BallRight(){
    Vector3 vel = pMyBall->m_particle->getVelocity();
    vel = vel + Vector3(5.0, 0.0, 0.0);
    pMyBall->m_particle->setVelocity(vel);
}

#pragma once
#include "vector3.h"

class Particle {

public:

    // Default constructor
    Particle(){
       position = Vector3(0.0,0.0,0.0);
       velocity = Vector3(0.0,0.0,0.0);
       acceleration = Vector3(0.0,0.0,0.0); 
       dInverseMass = 0.0; 
       bKinematic = false;
    };

    // Constructor
    Particle(Vector3 p, Vector3 v, Vector3 a) : 
        position(p), velocity(v), acceleration(a) {
            dInverseMass = 0.0;
            bKinematic = false;
        }

    // updates the physics of the particle based on elapsed time
    void update(double deltaTime);
    void printPosition();

    // get current position - needed for implementing graphics etc.
    Vector3 getPosition(){return this->position;}

    // get currect velocity
    Vector3 getVelocity(){return this->velocity;}

    // Does this particle have finite mass?
    bool hasFiniteMass(){return dInverseMass > 0.0;}

    // Helpers for mass
    void setMass(double m);
    double getMass();
    void setInverseMass(double im);
    double getInverseMass(){return this->dInverseMass;}
    

    // Helpers for being kinematic :)
    bool isKinematic(){return bKinematic;}
    void setKinematic(bool b){this->bKinematic = b;}

    // For adding a force to the forceResultant
    void addForce(Vector3 f);
    // Clears the forceResultant
    void clearForces();

    void setPosition(Vector3 pos){
        this->position = pos;
    }
    void setVelocity(Vector3 vel){
        this->velocity = vel;
    }
    void setAcceleration(Vector3 acc){
        this->acceleration = acc;
    }

private:

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    // The mass is stored as the inverse of the mass
    double dInverseMass;

    // Is this particle kinematic? i.e. no forces should affect the particle..
    bool bKinematic;

    // The sum of forces affecting this particle
    Vector3 forceResultant;

};
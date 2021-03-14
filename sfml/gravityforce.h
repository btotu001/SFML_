#pragma once
#include "force.h"

class GravityForce : public Force {

public:

    GravityForce(){
        this->gravity = Vector3(0.0,0.0,0.0);
    }

    // Constructor - only needs the vector for gravity
    GravityForce(Vector3 g) : gravity(g) {}

    // updates the force on the particle - duration not needed...
    void updateForce(Particle * p, double duration);

    // Setter for gravity
    void setGravity(Vector3 g){this->gravity = g;}

private:

    // The stored gravity vector
    Vector3 gravity;

};
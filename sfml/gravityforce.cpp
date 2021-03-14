#include "gravityforce.h"

// Updates the force on the particle
void GravityForce::updateForce(Particle * p, double duration){
    // Make sure the particle is not null!
    if (p != nullptr){
        // Only if the particle has finite mass and is not kinematic...
        if (p->hasFiniteMass()){
            //... add the gravity's acceleration*mass to the particle.
            // Remember! F = ma (a == g here...)
            p->addForce(this->gravity * p->getMass());
        }
    }
}

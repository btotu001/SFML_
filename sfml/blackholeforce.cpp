#include "blackholeforce.h"

void BlackholeForce::updateForce(Particle* p, double duration){

    // Make a vector from the particle to the "black hole"
    Vector3 diff =  this->pos - p->getPosition();
    double dist = diff.norm();

    if (dist < this->maxradius){
        Vector3 f = (diff * (1.0/(dist*dist))) * this->force; 
        p->addForce(f);
    }

}
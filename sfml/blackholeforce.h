#pragma once
#include "force.h"

class BlackholeForce : public Force {

public:

    BlackholeForce(){
        this->pos = Vector3(0.0, 0.0, 0.0);
        this->force = 0.0;
        this->maxradius = 0.0;
    }

    BlackholeForce(Vector3 p, double f, double mr) : 
    pos(p), force(f), maxradius(mr) {} 

    void updateForce(Particle * p, double duration);

    Vector3 getPosition(){return this->pos;}
    double getRadius(){return this->maxradius;}

    void setPosition(Vector3 p){this->pos = p;}
    void setForce(double f){this->force = f;}
    void setRadius(double r){this->maxradius = r;}

private:

    Vector3 pos;  // position of the blower
    double force;  // force strength - direction computed depending on particle pos
    double maxradius;  // max distance (or could be radius...)

};
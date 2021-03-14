#pragma once
#include "force.h"

class AirblowerForce : public Force {

public:

    AirblowerForce(){
        this->pos = Vector3(0.0, 0.0, 0.0);
        this->force = Vector3(0.0, 0.0, 0.0);
        this->maxdist = 0.0;
        this->maxheight = 0.0;
    }

    AirblowerForce(Vector3 p, Vector3 f, double md, double mh) : 
    pos(p), force(f), maxdist(md), maxheight(mh) {} 

    void updateForce(Particle * p, double duration);

    Vector3 getPosition(){return this->pos;}
    double getDist(){return this->maxdist;}
    double getHeight(){return this->maxheight;}

    void setPosition(Vector3 p){this->pos = p;}
    void setForce(Vector3 f){this->force = f;}
    void setDist(double d){this->maxdist = d;}
    void setHeight(double h){this->maxheight = h;}

private:

    Vector3 pos;  // position of the blower
    Vector3 force;  // force-vector
    double maxdist;  // max distance (or could be radius...)
    double maxheight;  // max height from the blower (not a very good way to do this...)

};
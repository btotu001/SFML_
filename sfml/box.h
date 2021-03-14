
#include <SFML/Graphics.hpp>
#include "particle.h"
#include "gameobject.h"

class Box : public GameObject {
    
public:
    Box();
    Box(double w, double h) : width(w), height(h) {};
    ~Box();

    Particle * m_particle;

    // Set's the particle
    void setPhysicsParticle(Particle * pParticle);

    // Returns the position of the ball on-screen
    sf::Vector2f getPos();

    // Get the radius
    double getWidth(){return this->width;}
    double getHeight(){return this->height;}

    void setWidth(double w){this->width = w;}
    void setHeight(double h){this->height = h;}

    // Updates the bounding box values
    void update();
//    double min_x, min_y, max_x, max_y;

private:
    /* data */
    double width, height;

    // shape???

};

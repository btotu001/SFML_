#include <SFML/Graphics.hpp>
#include "game.h"


class Renderer {

public:

    //renders the Game (pGame) to renderwindow
    void render(sf::RenderWindow* rw, Game* pGame);

private:
    //update shapes
    void updateShapes(Game* pGame);

    


    // Shapes
    sf::RectangleShape bgshape;
    sf::RectangleShape grass;

    sf::RectangleShape box;
    sf::RectangleShape box2;
    sf::RectangleShape box3;
    sf::RectangleShape box4;

    sf::CircleShape moving_circle;
    sf::RectangleShape airblower;
    sf::RectangleShape airblower_air;
    sf::RectangleShape airblower_other;
    sf::RectangleShape airblower_air_other;

    sf::CircleShape black_hole;
};

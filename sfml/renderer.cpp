#include "renderer.h"

void Renderer::updateShapes(Game* pGame) {


    //---------------------------------------------------
    // Shapes:
    //---------------------------------------------------
    // Background as black rectangle
    bgshape.setSize(sf::Vector2f(GameConstants::WinWidth,
        GameConstants::WinHeight));
    bgshape.setFillColor(sf::Color::Black);

    // Let's do the ground (and sky) with some more graphics shapes
    grass.setSize(sf::Vector2f(GameConstants::WinWidth, GameConstants::GrassHeight));
    grass.setPosition(0, GameConstants::WinHeight - grass.getSize().y);
    grass.setFillColor(sf::Color::Green);

    //test rendeering box
    box.setSize(sf::Vector2f(pGame->myBox.getWidth(), pGame->myBox.getHeight()));
    box.setPosition(pGame->myBox.getPos());
    box.setFillColor(sf::Color::Cyan);

    //test rendeering box
    box2.setSize(sf::Vector2f(pGame->myBox2.getWidth(), pGame->myBox2.getHeight()));
    box2.setPosition(pGame->myBox2.getPos());
    box2.setFillColor(sf::Color::Cyan);

    //test rendeering box
    box3.setSize(sf::Vector2f(pGame->myBox3.getWidth(), pGame->myBox3.getHeight()));
    box3.setPosition(pGame->myBox3.getPos());
    box3.setFillColor(sf::Color::Cyan);


    //test rendeering box
    box4.setSize(sf::Vector2f(pGame->myBox4.getWidth(), pGame->myBox4.getHeight()));
    box4.setPosition(pGame->myBox4.getPos());
    box4.setFillColor(sf::Color::Cyan);


    // A circle that is moved while rendering... this is for rendering only!
    //moving_circle.setRadius(myBall.getRadius());
    moving_circle.setFillColor(sf::Color::Red);
    moving_circle.setPosition(sf::Vector2f(10.0f, 400.0f));

    // Let's do an object for the airblower
    airblower.setSize(pGame->myBlower.getBaseSize());
    airblower.setPosition(pGame->myBlower.getBasePos());
    airblower.setFillColor(sf::Color::Blue);

    // And another one for the airflow... should be a gradient fill, maybe.
    airblower_air.setSize(pGame->myBlower.getAirflowSize());
    airblower_air.setPosition(pGame->myBlower.getAirflowPos());
    airblower_air.setFillColor(sf::Color::Yellow);

    // Let's do an object for the airblower
    airblower_other.setSize(pGame->myBlowerOther.getBaseSize());
    airblower_other.setPosition(pGame->myBlowerOther.getBasePos());
    airblower_other.setFillColor(sf::Color::Magenta);

    // And another one for the airflow... should be a gradient fill, maybe.
    airblower_air_other.setSize(pGame->myBlowerOther.getAirflowSize());
    airblower_air_other.setPosition(pGame->myBlowerOther.getAirflowPos());
    airblower_air_other.setFillColor(sf::Color::Yellow);

    // Black hole
    black_hole.setRadius(pGame->bhf.getRadius() / 100.0);
    black_hole.setPosition(sf::Vector2f(pGame->bhf.getPosition().getX() - black_hole.getRadius(),
        GameConstants::WinHeight - GameConstants::GrassHeight - pGame->bhf.getPosition().getY() - black_hole.getRadius()));
    black_hole.setFillColor(sf::Color::White); // Make it WHITE!!! :D
}


void Renderer::render(sf::RenderWindow* rw, Game* pGame) {

    //Update the shapes we need to draw
    this->updateShapes(pGame);

    // --------------------------------------------------------
    // "Rendering" part of the code:
    // --------------------------------------------------------
    rw->clear(); // clear window

    // All objects that we want to render should be drawn here
    //--------------------------------------------------------

    // Draw the "background" shape
    rw->draw(bgshape);

    // Draw the "grass"
    rw->draw(grass);

    // Draw the airblower
    rw->draw(airblower);
    rw->draw(airblower_air);

    // Draw the other airblower
    rw->draw(airblower_other);
    rw->draw(airblower_air_other);

    // Draw the black hole
    rw->draw(black_hole);

    //Draw the box
    rw->draw(box);
    rw->draw(box2);
    rw->draw(box3);
    rw->draw(box4);

    // Draw the moving small circle
    // Check particle position - must be 0 or greater

    if (pGame->particle.getPosition().getY() >= 0.0) {
        moving_circle.setPosition(pGame->myBall.getPos());
        moving_circle.setRadius(pGame->myBall.getRadius());
    }
    rw->draw(moving_circle);



    // "Copy the stuff to screen"
    rw->display();
}
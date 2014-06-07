
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "deplacementCamera.hpp"


void DeplacementCamera::operator()(sf::View &View, sf::Clock &timer)
{
    offset =  (double)(timer.getElapsedTime().asMicroseconds())/1000;


    // le deplacement de la map
    double offestZoom = offset * vitesseDeplacement;
    double offestMove =  scaleZoom * offestZoom;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )        {View.move( 0,      -offestMove);}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )     { View.move( 0,       offestMove);}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )     { View.move(-offestMove,  0);}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )    { View.move(offestMove,   0);}

    // le zoom
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) )
    {
        View.zoom(1.00f+offestZoom/ratioZoom);
        scaleZoom*=(1.0f+offestZoom/ratioZoom);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) )
    {
        View.zoom(1.00f-offestZoom /ratioZoom);
        scaleZoom*=(1.0f-offestZoom/ratioZoom);
    }

    // la gestion du "temps"
    // pourquoi c'est du statique ? Oo
  /*  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )    MonTimer::getSpeed() * 1.07;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) )    MonTimer::getSpeed() / 1.07;*/

    // clean
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) )     std::cout <<std::endl <<std::endl<<std::endl<<std::endl;

}

 void DeplacementCamera::imuable (sf::Shape& shape)
 {
    // le deplacement de la map
    double offestZoom = offset * vitesseDeplacement;
    double offestMove =  scaleZoom * offestZoom;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )        {shape.move( 0,      +offestMove);}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )     { shape.move( 0,       -offestMove);}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )     { shape.move(+offestMove,  0);}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )    { shape.move(-offestMove,   0);}

    // le zoom
    sf::Vector2f scale = shape.getScale();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) )
    {
        double facteur = (1.00f+offestZoom/ratioZoom);
        shape.setScale(scale.x * facteur, scale.y * facteur);

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) )
    {
        double facteur = (1.00f-offestZoom/ratioZoom);
        shape.setScale(scale.x * facteur, scale.y * facteur);

    }

 }

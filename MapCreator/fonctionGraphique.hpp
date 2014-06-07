#ifndef FONCTION_GRAPHIQUE_HPP
#define FONCTION_GRAPHIQUE_HPP
#include <SFML/Graphics.hpp>
#include <list>
#include <cmath>
#include <memory>
//void drawHexagone (sf::Shape &Polygon ,int cote,sf::Color couleur);
sf::ConvexShape createHexagone (int cote, sf::Color couleur);


template <class T>
void placePositionableIJ (const int j,const int i, T & positionable,int cote)
{
    double sqrt3 = sqrt(3.0);
    double x = 0;
    double y = 0;
    cote++;

    x += cote*sqrt3*i + j*(sqrt3/2)*cote;
    y += (double)j*1.5*(double)cote;



    positionable.setPosition(sf::Vector2f(x,y));
}

sf::Vector2<int> mouseToXY(int mouseX, int mouseY, int cote);
sf::Vector2<int> XYtoIJ (sf::Vector2<int> XY ,int cote);
sf::Vector2<double> IJtoXY (sf::Vector2<int> IJ ,int cote);

void gestionTouches (sf::View &View,sf::Clock &timer);



/*
bool plusDeVie(Cible*);
void afficheMonstre   (sf::RenderWindow &App, sf::Sprite  &SpriteMoob ,Monstre* monMoob,int cote, int offSetX, int offSetY ,  std::list<Tour*> &listTour);
void afficheConstructible  (sf::RenderWindow &App, sf::Sprite &SpriteTower ,sf::Shape &PolygonPorte,Constructible* maCons,int cote, int offSetX, int offSetY );
*/

#endif




#include "fonctionTerrain.hpp"



std::vector<sf::Vector2<int>> calculCercle(unsigned int range)
{
    // initilisation
    std::vector<sf::Vector2<int> > caseCote;

    // si il a une range de moins de 1 il ne connais que lui
    if ( range < 1)
    {
        caseCote.push_back(sf::Vector2<int>(0,0));
        return caseCote;
    }

    sf::Vector2<int> XYcentre;
    XYcentre.x = 0;
    XYcentre.y = 0;

    // les 6 points principaux
    sf::Vector2<int> XYest ;
    XYest.x = XYcentre.x + range;
    XYest.y = XYcentre.y;
    sf::Vector2<int> XYouest ;
    XYouest.x = XYcentre.x - range;
    XYouest.y = XYcentre.y;

    sf::Vector2<int> XYsud_ouest ;
    XYsud_ouest.x = XYcentre.x - range;
    XYsud_ouest.y = XYcentre.y + range ;
    sf::Vector2<int> XYnord_ouest ;
    XYnord_ouest.x = XYcentre.x ;
    XYnord_ouest.y = XYcentre.y - range ;

    sf::Vector2<int> XYnord_est ;
    XYnord_est.x = XYcentre.x + range;
    XYnord_est.y = XYcentre.y - range;
    sf::Vector2<int> XYsud_est ;
    XYsud_est.x = XYcentre.x;
    XYsud_est.y = XYcentre.y + range;


    // avec un range de 1 il y pas de "cote" avec un range de 2 le coté vaut 1.. avec 3 _> 2 ext
    for ( unsigned int i = 1 ; i <= range-1 ; i++)
    {
        sf::Vector2<int> cote;

        // est vers NE
        cote.x = XYest.x;
        cote.y = XYest.y - i;
        caseCote.push_back(cote);
        // NE vers NO
        cote.x = XYnord_est.x - i;
        cote.y = XYnord_est.y ;
        caseCote.push_back(cote);

        //  NO vers O
        cote.x = XYnord_ouest.x - i;
        cote.y = XYnord_ouest.y + i;
        caseCote.push_back(cote);
        //  O vers SO
        cote.x = XYouest.x;
        cote.y = XYouest.y + i;
        caseCote.push_back(cote);
        //  sO vers SE
        cote.x = XYsud_ouest.x+i;
        cote.y = XYsud_ouest.y;
        caseCote.push_back(cote);

         //  sE vers E
        cote.x = XYsud_est.x+i;
        cote.y = XYsud_est.y -i;
        caseCote.push_back(cote);
    }

    // on ajoute les coins
     caseCote.push_back(XYest);
     caseCote.push_back(XYnord_est);
     caseCote.push_back(XYnord_ouest);
     caseCote.push_back(XYouest);
     caseCote.push_back(XYsud_ouest);
     caseCote.push_back(XYsud_est);

     return caseCote;
}

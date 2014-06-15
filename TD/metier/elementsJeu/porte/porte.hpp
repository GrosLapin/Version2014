#ifndef PORTE_HPP
#define PORTE_HPP

#include <vector>
#include <utility>  // pair
#include <SFML/System/Vector2.hpp>

#include "enumPorte.hpp"
#include "../../terrain/fonctionTerrain.hpp"

/**
    Une porte est une forme avec une range (scale ?) on peut avoir par exemple un cercle de taille 2
    ou une etoile de taille 3
    La porte est centré en 0.0 et ne s'occupe pas de la map, le raccords avec la map et fait dans le foncteur
    qui va bien

    Note : normalement il devrait pas y avoir de problemes, les operator de move / copy sont mis par defaut
*/
class Portee
{
    public :
        Portee (TypeDePorte forme, int range) ;

        std::vector<sf::Vector2<int>> getZoneVirturelle () { return zoneVirtuelle ;}
        int getRange () { return range; }
        TypeDePorte getForme () { return forme; }
    private :
        std::vector<sf::Vector2<int>> zoneVirtuelle;
        int range;
        TypeDePorte forme;

};
#endif

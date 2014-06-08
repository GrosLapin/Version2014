#ifndef UTILITAIRE_HPP
#define UTILITAIRE_HPP

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/ring.hpp>





template <class Map, class Key>
bool contains (Map uneMap, Key uneKey)
{
    return ( uneMap.find(uneKey) != uneMap.end());
}

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}



/// pourquoi faire simple quand on peut faire du c++
template <typename T>
void sous_concanate(std::ostringstream& stm,const T& valeur)
{
    stm << valeur;
}

template <typename U, typename... T>
void sous_concanate(std::ostringstream& stm,const U& head,const T&... tail)
{
    stm << head;
    sous_concanate(stm,tail...);
}

template <class... Types>
std::string concatenate(const Types&... values)
{
    std::ostringstream stm ;
    sous_concanate(stm, values... );
    return stm.str();
}


template <class T>
bool operator== (std::shared_ptr<T> shp, T t)
{
    return ( (*(shp.get())) == t ) ;
}


template <class T>
std::ostream& operator<<(std::ostream &os, const sf::Vector2<T> &vect)
{
    os << "(" <<vect.x << "," << vect.y << ")";
    return os;
}
template <class T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &vect)
{
    for ( const T& elem : vect)
    {
         os << elem << " | ";
    }
    os << std::endl;
    return os;
}

template <class T>
std::vector<sf::Vector2f> getAllPoints(const T& cs)
{
    // il semblerais qu'il puisse y avoir des bugs avec les "set possition..."
    std::vector<sf::Vector2f> retour;

    int nb = cs.getPointCount();
    sf::Transform trans = cs.getTransform();
    for ( int i = 0 ; i < nb ; i++)
    {
        retour.push_back(trans.transformPoint(cs.getPoint(i)));
    }
    return retour;
}
/*  c'etait pour regler un bug je garde au cas ou ça soit plus optimiser mais a voir plus tard
template <>
std::vector<sf::Vector2f> getAllPoints <sf::RectangleShape> (const sf::RectangleShape& cs)
{
    // il semblerais qu'il puisse y avoir des bugs avec les "set possition..."
    std::vector<sf::Vector2f> retour;

    retour.emplace_back(cs.getPosition().x                ,cs.getPosition().y);
    retour.emplace_back(cs.getPosition().x+cs.getSize().x ,cs.getPosition().y);
    retour.emplace_back(cs.getPosition().x+cs.getSize().x ,cs.getPosition().y+ cs.getSize().y);
    retour.emplace_back(cs.getPosition().x                ,cs.getPosition().y+cs.getSize().y);

    return retour;
}*/

// au lieux de spécifier, je surcharge semberait que si non ça fasse un bug relou a la compil... si le fait une spécifiation
// et donc que je laisse le corps ici , j'ai une multiple def a la con
std::vector<sf::Vector2f> getAllPoints (const sf::RenderWindow& cs);

template <class T>
std::vector<sf::Vector2f>    getAllPoints (const sf::Rect< T >& rect)
{
    std::vector<sf::Vector2f>  retour;

    retour.emplace_back(rect.left,rect.top);
    retour.emplace_back(rect.left+rect.width,rect.top);
    retour.emplace_back(rect.left+rect.width,rect.top+rect.height);
    retour.emplace_back(rect.left,rect.top+rect.height);


    return retour;
}

template <class T>
std::vector<sf::Vector2f> getRing(const T& qqch)
{
    std::vector<sf::Vector2f> retour = getAllPoints(qqch);
    boost::geometry::correct(retour);
    return retour;
}

class Terrain;
Terrain loadMap(std::string p_fichier);
bool saveMap(Terrain &terrain, std::string p_fichier);
std::string getDossier(std::string cheminExe);

#endif // UTILITAIRE_HPP

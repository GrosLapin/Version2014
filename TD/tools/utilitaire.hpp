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

#include "../metier/terrain/terrain.hpp"
#include "../metier/terrain/case.hpp"

std::string getDossier(std::string cheminExe)
{
    int possition = cheminExe.find_last_of("/\\");
    return  cheminExe.substr(0,possition) +"/";
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
template <>
std::vector<sf::Vector2f> getAllPoints <sf::RenderWindow>(const sf::RenderWindow& cs)
{
    std::vector<sf::Vector2f> retour;

    retour.emplace_back(0,0);
    retour.emplace_back(0,cs.getSize().y);
    retour.emplace_back(cs.getSize().x,cs.getSize().y);
    retour.emplace_back(cs.getSize().x,0);

    return retour;
}

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

bool loadMap(Terrain &terrain, std::string p_fichier)
{

    std::ifstream fichier(p_fichier.c_str(), std::ios::in);  // on ouvre en lecture
    if(fichier)  // si l'ouverture a fonctionné
    {
        std::string line;  // déclaration d'une chaîne qui contiendra la ligne lue
        while(getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
        {
            std::istringstream iss;
            iss.str(line);
            std::string i, j;
            iss >> i >> j ;

            terrain.addCase(std::atoi(i.c_str()), std::atoi(j.c_str()));
        }
        fichier.close();
    }

    return false;

}

bool saveMap(Terrain &terrain, std::string p_fichier)
{

    std::ofstream fichier(p_fichier.c_str(),  std::ios::out |  std::ios::trunc );  //déclaration du flux et ouverture du fichier
    if(fichier)  // si l'ouverture a réussi
    {

        for ( auto& shared : terrain  )
        {
            fichier << shared.get()->getI() << " " << shared.get()->getJ() <<std::endl;

        }

        fichier.close();  // on referme le fichier
        return true;
    }

    return false;

}


#endif // UTILITAIRE_HPP

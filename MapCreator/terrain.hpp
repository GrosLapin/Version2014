#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#include <vector>
#include <map>
#include <string>
#include <memory>
class Case;

class Terrain
{
    public :
        bool addCase(int i, int j);
        bool removeCase (int i, int j);
        Case* getCase(int i, int j) ;

        // les itérators afin d'utiliser les for(:) de c++ 11
        typedef std::vector<Case>::iterator iterator;
        typedef std::vector<Case>::const_iterator const_iterator;

        iterator begin() { return listCase.begin() ;}
        const_iterator begin() const { return listCase.begin() ;}

        iterator end() { return listCase.end() ;}
        const_iterator end() const { return listCase.end() ;}


        // plus a des fin de debug qu'autre chose
        int taille () { return listCase.size() ;}

    private :
        std::vector<Case> listCase;
        std::map< std::string , int > mapIndice; //je suis pas sur que ça soit le meuiller moyen de representer la mémoir map <int map <int case *>


};
#endif

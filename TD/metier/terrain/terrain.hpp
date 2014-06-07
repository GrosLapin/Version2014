#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#include <vector>
#include <map>
#include <string>
#include <memory>
class Case;
// il faudrait peut etre avoir un boost itérator pour avoir un itérator sur une ref plutot que sur un weak-ptr
class Terrain
{
    public :
        bool addCase(int i, int j);
        bool removeCase (int i, int j);

        // j'aurais bien retourné une ref, mais je peux pas pour le cas ou i/j n'est pas dans le tableau
        // faudrait retourner un pointeur / null : Envisageable mais a reflechir
        std::weak_ptr<Case> getCase(int i, int j) ;

        int taille () { return listCase.size() ;}
        typedef std::vector<std::shared_ptr<Case> >::iterator iterator;
        typedef std::vector<std::shared_ptr<Case> >::const_iterator const_iterator;

        iterator begin() { return listCase.begin() ;}
        const_iterator begin() const { return listCase.begin() ;}

        iterator end() { return listCase.end() ;}
        const_iterator end() const { return listCase.end() ;}

    private :
        std::vector<std::shared_ptr<Case> > listCase;
        std::map< std::string , std::weak_ptr<Case> > mapCase; //je suis pas sur que ça soit le meuiller moyen de representer la mémoir map <int map <int case *>


};
#endif

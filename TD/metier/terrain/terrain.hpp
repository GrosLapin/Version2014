#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#include <vector>
#include <map>
#include <string>
#include <memory>

class Case;

// l'idée pour pas etre emmerder c'est de faire un terrain qui est pas modifiable
// comme ça je passe des * et des ref valide est c'est cool
// de toute facon il a pas vocation a bouger en jeu.
/// LE TERRAIN DE TD et de MAP_EDITOR ne sont pas les memes !!!
class Terrain
{
    public :
        template<class ConteneurDePaireDeInt>
        Terrain (ConteneurDePaireDeInt conteneur)
        {
            decltype(conteneur.begin()) it = conteneur.begin();
            int i =0 ;
            for ( ; it != conteneur.end() ; it++ )
            {
                // pour la lisibilité et que le compilateur guelle si les types sont mauvais
                int i = (*it).first;
                int j = (*it).second;
                listCase.push_back(Case(i,j));
                i++;
                std::cout << i << std::endl;
            }

            // maintenant que le vecteur est charger on fait le lien avec la map sans risque
            for (Case& uneCase : listCase)
            {
                // fonction qui fait le liens des cases entre elles et qui place dans la mapCase
                placeCase(uneCase);
            }
        }

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
        void placeCase(Case& uneCase);
        std::vector<Case> listCase;
        std::map< std::string , Case* > mapCase; //je suis pas sur que ça soit le meuiller moyen de representer la mémoir map <int map <int case *>


};


#endif

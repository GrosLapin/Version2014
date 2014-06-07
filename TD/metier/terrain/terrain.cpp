#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

#include "terrain.hpp"
#include "case.hpp"
//#include "../../tools/utilitaire.hpp"

using namespace std;

bool Terrain::addCase(int i, int j)
{
    // la fleme de l'ecrir deux fois
    std::ostringstream oss;
    oss <<  i <<  "_"  << j;
    std::string ij = oss.str();
    oss.str("");

    // si la case n'esite pas deja
    if (mapCase.find(ij) == mapCase.end() )
    {
        //std::cout << ij  << std::endl;
        // ajout de la case dans la liste
        listCase.push_back(make_shared<Case>(i,j));

        // ajoute de la case dans la map
        std::weak_ptr<Case> nouvelleCase_weak = listCase.back();
        mapCase[ij] = nouvelleCase_weak;
        int copieI = i, copieJ = j;
        // on fait le liens avec les cases existantes
        for (int k = DebutDirection ; k <= FinDirection ; k++)
        {
            // now IJ sont ceux du voisin dans la direction "k"
            i = copieI;
            j = copieJ;
            IJvoisin((Direction)k,i,j);

            // si cette case existe
            oss << i <<  "_"  << j;
            std::string ij_voisin = oss.str();

            oss.str("");

            if ( mapCase.find(ij_voisin) != mapCase.end())
            {
                std::weak_ptr<Case> voisin_weak = mapCase[ij_voisin];
                if ( auto voisin = voisin_weak.lock() )
                {
                    // On ajoute cette case comme voisin ( et vis versa )
                    if ( auto nouvelleCase = nouvelleCase_weak.lock() )
                        nouvelleCase->addVoisin((Direction)k,voisin_weak);
                    else
                        std::cerr << " miracle, bug imposible " ;


                }

            }


        }

        return true;
    }

    // existe deja
/*
    auto weak = mapCase[ij];
    if ( auto sh = weak.lock() )
    {
        cout <<  (*sh).getI() << " " <<  (*sh).getJ() ;
    }
    else
        cout << "fail lock";
    cout << ij << "  false \n";*/
    return false;
}


bool Terrain::removeCase (int i, int j)
{
    std::ostringstream oss;
    oss << i <<  "_"  << j;
    std::string ij = oss.str();

    // si la case esite
    if (mapCase.find(ij) != mapCase.end() )
    {
        // recherhce de l'id de la case
        auto it = std::find(listCase.begin(),listCase.end(),mapCase[ij].lock());


        listCase.erase(it);
        mapCase.erase(mapCase.find(ij));

        return true;
    }

    // rien a a supprimer si ça existe pas
    return false;

}

std::weak_ptr<Case> Terrain::getCase(int i, int j)
{
    std::ostringstream oss;
    oss << i <<  "_"  << j;
    std::string ij = oss.str();


    if (mapCase.find(ij) != mapCase.end() )
    {

        return mapCase[ij];
    }

    // rien a a supprimer si ça existe pas
    return std::weak_ptr<Case>();

}

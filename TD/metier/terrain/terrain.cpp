#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

#include "terrain.hpp"
#include "case.hpp"
#include "../../tools/utilitaire.hpp"

using namespace std;



Case* Terrain::getCase(int i, int j)
{
    std::string ij = concatenate(i,"_",j);
    if (contains(mapCase,ij))
    {
        return mapCase[ij];
    }
    // rien a a supprimer si ça existe pas
    return nullptr;

}

void Terrain::placeCase(Case& uneCase)
{
    // J'ai eu un comportement etrange une fois ici : DANGER
    int i = uneCase.getI();
    int j = uneCase.getJ();
    std::string ij = uneCase.toString();

    // si la case n'esite pas deja : normalement ça devrait pas se produire
    if (!contains(mapCase,ij))
    {

        mapCase[ij] = &uneCase;

        int copieI = i, copieJ = j;
        // on fait le liens avec les cases existantes
        for (int k = DebutDirection ; k <= FinDirection ; k++)
        {
            // now IJ sont ceux du voisin dans la direction "k"
            i = copieI;
            j = copieJ;
            IJvoisin((Direction)k,i,j);

            // si cette case existe
            std::string ij_voisin = concatenate(i,"_",j);
            if (contains(mapCase,ij_voisin))
            {
                Case* voisin_ptr = mapCase[ij_voisin];
                if ( voisin_ptr != nullptr )
                {
                    // On ajoute cette case comme voisin ( et vis versa )
                    uneCase.addVoisin((Direction)k,voisin_ptr);
                }
            }
        }

        /// je suis pas sur que ça soit tres beau, mais j'ai besoin de la map dans le foncteur de range
        uneCase.setTerrain(this);
    }
    else
    {
        std::cerr << "DANGER "<< mapCase[ij]->getI() << " " <<  mapCase[ij]->getJ()  << std::endl;
    }
    // la case existait déjà, on a rien fait
}

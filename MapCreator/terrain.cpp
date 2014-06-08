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
    // J'ai eu un comportement etrange une fois ici : DANGER
    std::string ij = concatenate(i,"_",j);

    // si la case n'esite pas deja
    if (!contains(mapIndice,ij))
    {
        listCase.push_back(Case(i,j));

        /// ajoute de la case dans la map NE MARCHE PAS CE N EST PAS DES POINTEUR
        Case& nouvelleCase_ptr = listCase.back();
        mapIndice[ij] = listCase.size()-1;

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
            if (contains(mapIndice,ij_voisin))
            {
                Case* voisin_ptr = mapIndice[ij_voisin];
                if ( voisin_ptr != nullptr )
                {
                    // On ajoute cette case comme voisin ( et vis versa )
                    nouvelleCase_ptr.addVoisin((Direction)k,voisin_ptr);
                }
            }
        }
        // on a bien fait l'ajout
        return true;
    }
    // la case existait déjà, on a rien fait
    return false;
}


bool Terrain::removeCase (int i, int j)
{
    std::string ij = concatenate(i,"_",j);

    // si la case esite
    if (contains(mapIndice,ij))
    {
        // recherhce de l'id de la case
       int indice = mapIndice[ij];

        // je dois parcourir les voisins pour leurs dire que la case est morte
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

            if ( contains(mapIndice,ij_voisin))
            {
                int voisin_indice = mapIndice[ij_voisin];

                // On l'informe que ce voisin n'existe plus
                listCase[voisin_indice].removeVoisin((Direction)k);
            }
        }

        // il faut maintenant metre à jours tous les indices
        for ( int i = indice +1 ; i < listCase.size() ; i ++)
        {
            string key = concatenate(listCase[i].getI(),"_",listCase[i].getJ());
            mapIndice[key]--;
        }

        // les indices sont de type "size-1" donc de "0 a size-1" donc normalement j'ai bon
        listCase.erase(listCase.begin()+indice);
        // et je suprime la case de la map qui va bien
        mapIndice.erase(mapIndice.find(ij));

        return true;
    }

    // rien a a supprimer si ça existe pas
    return false;

}

Case* Terrain::getCase(int i, int j)
{
    std::string ij = concatenate(i,"_",j);
    if (contains(mapIndice,ij))
    {
        return mapIndice[ij];
    }
    // rien a a supprimer si ça existe pas
    return nullptr;

}

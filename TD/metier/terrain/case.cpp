#include "case.hpp"
#include <iostream>

using namespace std;
Case::Case(int p_i, int p_j) :
    i ( p_i ),
    j ( p_j ),
    voisin ({{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}}),
    franchissable (true),
    occupe (false),
    setPositionable ()
{
    // pour la double ({{ }}) => bug Gcc qui respecte pas le stendard
    // http://stackoverflow.com/questions/8192185/using-stdarray-with-initialization-lists
}

// semblerais que si on le fasse pas il puisse y avoir un bug (pas d'initialisaiton des types de base)
/*Case::Case() :
    i ( 0 ),
    j ( 0 ),
    franchissable (true),
    occupe (false)
{}*/

std::string Case::toString() const
{
    std::ostringstream oss;
    oss << i <<  "_"  << j;
    return oss.str();
}

bool Case::quelleDirection(const Case* p_voisin,Direction &out_dir)
{
    /// je pense que la fonction peut s'optimiser avec un calcul au lieu de faire un parcours de boucle.
    bool pasTrouve = true;
    int dir = DebutDirection;
    while (pasTrouve && dir <=FinDirection )
    {
        Case* unVoisin = voisin[(Direction)dir];
        if ( unVoisin != nullptr )
        {
            // operator == sur i j
            if ( unVoisin == p_voisin)
            {
                pasTrouve= false;
            }
            else
            {
                dir+=1;
            }
        }
        else
        {
            dir+=1;
        }
    }
    out_dir = (Direction)dir;
    return !pasTrouve;
}

Case::~Case()
{
    for (int k = DebutDirection ; k <= FinDirection ; k++)
    {
        if (voisin[k] != nullptr)
        {
           voisin[k]->voisin[directionOppose((Direction)k)] = nullptr;
        }
    }
}

Case* Case::getVoisin(const Direction& direction)
{
    return voisin[direction];
}

void Case::addVoisin(const Direction& direction, Case*  p_voisin)
{
    // on ne peut ajouter un voisin que la case est "libre"
    if ( voisin[direction]==nullptr && p_voisin != nullptr)
    {
        voisin[direction] = p_voisin;
        p_voisin->addVoisin(directionOppose(direction),this);
    }
}


/*


void Case::monstreArrive(Monstre* moob)
{
    listeMonstre.insert(moob);
}
void Case::monstrePart  (Monstre* moob)
{
    listeMonstre.erase(moob);
}

void Case::ajoutConstructible (Constructible* p_tour)
{
     listeConstructible.insert(p_tour);
}

void Case::suppressionConstructible(Constructible* p_tour)
{
     listeConstructible.erase(p_tour);
}
void Case::ajoutEffect    (Effet * p_Effect)
{

    // 1) on ajoute cette effet a notre liste d'effet
    listEffets.push_back(p_Effect);

    // 2) on ajoute cette effet comme effect "subie" au gens sur la case
    std::set<Monstre* >::iterator itMonstre;
    std::set<Constructible* >::iterator itConstr;

    // et on demande a tout les cible d'ajouter l'effet
    for ( itMonstre = listeMonstre.begin(); itMonstre != listeMonstre.end(); ++itMonstre )
    {
        (*itMonstre)->addEffetPropre(p_Effect);
    }
    for ( itConstr = listeConstructible.begin(); itConstr != listeConstructible.end(); ++itConstr )
    {
        (*itConstr)->addEffetPropre(p_Effect);
    }

}
void  Case::removeEffect   (Effet * p_Effect)
{

    std::set<Monstre* >::iterator itMonstre;
    std::set<Constructible* >::iterator itConstr;

    // et on demande a tout les cible de supprimer l'effet
    for ( itMonstre = listeMonstre.begin(); itMonstre != listeMonstre.end(); ++itMonstre )
    {
      //   std::cout << " suppression d'un effet de la tours sur un monstre" << std::endl;
        (*itMonstre)->removeEffetPropre(p_Effect);
    }
     for ( itConstr = listeConstructible.begin(); itConstr != listeConstructible.end(); ++itConstr )
    {
      //  std::cout << " suppression d'un effet de la tours sur une tour" << std::endl;
        (*itConstr)->removeEffetPropre(p_Effect);
    }
    // et on supprime réellement l'effet
    listEffets.remove(p_Effect);

}
*/

#include "case.hpp"
#include <iostream>

using namespace std;
Case::Case(int p_i, int p_j) :
    i ( p_i ),
    j ( p_j ),
    franchissable (true),
    occupe (false)
{}

// semblerais que si on le fasse pas il puisse y avoir un bug (pas d'initialisaiton des types de base)
Case::Case() :
    i ( 0 ),
    j ( 0 ),
    franchissable (true),
    occupe (false)
{}

std::string Case::toString() const
{
    std::ostringstream oss;
    oss << i <<  "_"  << j;
    return oss.str();
}

bool Case::quelleDirection(const Case& p_voisin,Direction &out_dir)
{
    /// je pense que la fonction peut s'optimiser avec un calcul au lieu de faire un parcours de boucle.
    bool pasTrouve = true;
    int dir = DebutDirection;
    while (pasTrouve && dir <=FinDirection )
    {
        if ( auto candidat = voisin[(Direction)dir].lock() )
        {
            if ( (*candidat) == p_voisin)
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
    /*
    for (int k = DebutDirection ; k <= FinDirection ; k++)
    {
        if (voisin[k] != NULL)
        {

           voisin[k]->voisin = NULL;
        }
    }*/
}

std::weak_ptr<Case> Case::getVoisin(const Direction& direction)
{
    return voisin[direction];
}

void Case::addVoisin(const Direction& direction, std::weak_ptr<Case>  p_voisin)
{
    // on ne peut ajouter un voisin que la case est "libre"
    auto cetteCase = voisin[direction].lock() ;
    auto voisin_shared = p_voisin.lock() ;
    if ( ! cetteCase)
    {
        voisin[direction] = p_voisin;
        if (voisin_shared )
            voisin_shared->addVoisin(directionOppose(direction),shared_from_this());
        else
            std::cout << "ceci ne devrait pas arriver "<< endl;
    }
   /* auto retour = voisin.insert(pair<Direction,reference_wrapper<Case>> (direction,reference_wrapper<Case>(p_voisin)));
    if ( retour.second )
    {
        p_voisin.addVoisin(directionOppose(direction), (*this) );
    }*/
    /*
    // on ne peut ajouter un voisin que la case est "libre"
    if ( voisin[direction] == NULL)
    {
        // on ajoute le voisin
        voisin[direction] = p_voisin;
        // et on dit au voisin de nous ajouter
        p_voisin->addVoisin(directionOppose(direction),this);
        // on evite la boucle infine avec le if == NULL

        //std::cout << "(" << i << "," << j << ") a pour voisin ("<<p_voisin->i<< "," << p_voisin->j << ")" << std::endl;
    }*/
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

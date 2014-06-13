#include "positionnable.hpp"
#include "../terrain/case.hpp"
#include <iostream>
using namespace std;
Positionnable::Positionnable (Case* p_position) : position(p_position)
{
    if ( nullptr != position )
    {
        position->addPositionnable(this);
    }
}

/// _______________________________________________
/// _____j'ai declarer un destructor du____________
/// _________coup je devrais pas pouvoir___________
/// ____________faire de copie_____________________
/// _______________________________________________
Positionnable::~Positionnable ()
{
    if ( nullptr != position )
    {
        position->removePositionnable(this);
    }
}

/// Permet de changer de case (gere le cas null avant ou null apres)
void Positionnable::changeCase (Case* nouvelleCase)
{

    // 1) Il faut faire savoir à la case que le positionnable s'en va:
    if ( nullptr != position )
    {
        position->removePositionnable(this);
    }

    // 2) on change de case
    position = nouvelleCase;

    // 3) on fait savoir à la nouvelle case qu'il y a un nouveau positionable
    if ( nullptr != position )
    {
        position->addPositionnable(this);
    }

}

/*
 size_t HashWeakPositionnable::operator()(const Positionnable* positionnalbe_ptr) const {
    size_t retour = 0 ;

    Case* saCase_ptr = positionnalbe_ptr->getPosition();

    if ( nullptr != positionnalbe_ptr && nullptr !=  saCase_ptr )
    {
        retour = saCase_ptr->getI()* 100 + saCase_ptr->getI();

    }
    return retour;
}*/

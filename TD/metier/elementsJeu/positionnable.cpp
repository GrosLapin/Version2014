#include "positionnable.hpp"
#include "../terrain/case.hpp"
#include <iostream>
using namespace std;
Positionnable::Positionnable (Case* p_position) : position(p_position)
{

}


/// Permet de changer de case (gere le cas null avant ou null apres)
void Positionnable::changeCase (Case* nouvelleCase)
{

    // 1) Il faut faire savoir à la case que le positionnable s'en va:
    if ( nullptr != position )
    {
        quitteCase(position);
    }

    // 2) on change de case
    position = nouvelleCase;

    // 3) on fait savoir à la nouvelle case qu'il y a un nouveau positionable
    if ( nullptr != position )
    {
        arriveCase(position);
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

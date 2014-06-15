#include "cible.hpp"
#include "../terrain/case.hpp"
// il y aura surement des effects qui viendrons se mettre la
bool Cible::subirDommage(double dommage)
{
    // 1 ) calcule de la reduction de dmg a la lol
    double reduction =  armure / (armure + 100) ;

    // 2 ) on subit les dmgs
    pv -= dommage*reduction;

    // 3 ) je garde ça parce que c'etait comme ça ma a voir,
    if (pv>0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


Cible::Cible(Case* position,double maxPv,bool pvolante, bool pvisible) :
Positionnable::Positionnable(position),
volante(pvolante),
visible(pvisible),
pv(maxPv),
pvMax(maxPv),
armure(0)
{
     if ( nullptr != Positionnable::position )
        {
            Positionnable::position->addCible(this);
        }
};

Cible::~Cible ()
{
    if ( nullptr != Positionnable::position )
    {
        Positionnable::position->removeCible(this);
    }
}

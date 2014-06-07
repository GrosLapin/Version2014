#include "positionnable.hpp"
#include "../terrain/case.hpp"
#include <iostream>
Positionnable::Positionnable (std::weak_ptr<Case> p_position)
{
    position = p_position;
    if ( auto shared = position.lock() )
    {
        Case& uneCase = (*shared.get());
        std::cout <<"ici";
        std::weak_ptr<Positionnable> wk = shared_from_this();
         std::cout <<"ici";

                 uneCase.addPositionnable( wk);
    }
}

void Positionnable::changeCase (std::weak_ptr<Case> nouvelleCase)
{
    position = nouvelleCase;
}


 size_t HashWeakPositionnable::operator()(const std::weak_ptr<Positionnable> &weak_posi) const {
    size_t retour = 0 ;
    if ( auto sharedPosi = weak_posi.lock())
    {
        if ( auto sharedCase = sharedPosi.get()->getPosition().lock() )
        {
            retour = sharedCase.get()->getI()* 100 + sharedCase.get()->getI();
        }
    }

     return retour;
   }

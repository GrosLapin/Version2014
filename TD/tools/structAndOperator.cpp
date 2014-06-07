#include "structAndOperator.hpp"
#include "../metier/elementsJeu/positionnable.hpp"

bool operator == (std::weak_ptr<Positionnable> const& un, std::weak_ptr<Positionnable> const& deux)
{
    if ( auto shared1 = un.lock() )
    {
        if ( auto shared2 = deux.lock() )
        {
            return un == deux;
        }
    }

    return false;
}


#ifndef STRUCTANDOPERATOR_HPP
#define STRUCTANDOPERATOR_HPP

#include <memory>
class Positionnable;
bool operator == (std::weak_ptr<Positionnable> const& un, std::weak_ptr<Positionnable> const& deux);

struct pairIJ
{
    int i;
    int j;
};
#endif

#ifndef POSITIONNABLE_HPP
#define POSITIONNABLE_HPP


#include <memory>
#include <string>
class Case;

// abs or not ?
class Positionnable :  public std::enable_shared_from_this<Positionnable>
{
    public :
        virtual std::weak_ptr<Case> getPosition() const  { return position;};


        Positionnable (std::weak_ptr<Case> p_position);

        /* Pour moi devrait etre constructeur et le destructeur */
        /*virtual void arriveEnJeu (std::weak_ptr<Case> p_position);
        virtual void quitteLeJeu ();*/


        virtual void changeCase (std::weak_ptr<Case> nouvelleCase);

        std::weak_ptr<Case> getPosition () { return position; };


    protected :

        // localisation
        std::weak_ptr<Case> position;

};

class HashWeakPositionnable
{
public :
    size_t operator()(const std::weak_ptr<Positionnable> &weak_posi) const;
};

#endif

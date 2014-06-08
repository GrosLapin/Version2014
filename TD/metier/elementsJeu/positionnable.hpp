#ifndef POSITIONNABLE_HPP
#define POSITIONNABLE_HPP


#include <memory>
#include <string>
#include <iostream>
class Case;

// abs or not ?
class Positionnable
{
    public :
        // Le virtual doit etre pour l'heritage en diamant
        virtual Case* getPosition() const  { return position;};


        Positionnable (Case* p_position);
        virtual ~Positionnable ();

        /*virtual void arriveEnJeu (std::weak_ptr<Case> p_position);
        virtual void quitteLeJeu ();*/


        virtual void changeCase (Case* nouvelleCase);

        Positionnable& operator=(Positionnable&& other) {
            position = std::move(other.position);
            std::cout << "move assigned\n";
            return *this;
        }

        Positionnable (Positionnable&& other) {
            position = std::move(other.position);
            std::cout << "move constructor \n";

        }


    protected :

        // localisation
        Case*  position;

};

class HashWeakPositionnable
{
public :
    size_t operator()(const Positionnable* positionnalbe_ptr) const;
};

#endif

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
        //virtual ~Positionnable () {}

        /*virtual void arriveEnJeu (std::weak_ptr<Case> p_position);
        virtual void quitteLeJeu ();*/


        // un peu de nvi (parce que j'aime ça
        void changeCase (Case* nouvelleCase);
        virtual void quitteCase(Case *) = 0 ; // a specifier au niveau de la tour et du monstre
        virtual void arriveCase(Case *) = 0 ;
        Positionnable& operator=(Positionnable&& other) = delete;
        Positionnable (Positionnable&& other) = delete;
        Positionnable& operator=(const Positionnable& other) = delete;
        Positionnable (const Positionnable& other) = delete;

/*
Le comportement est FAUX, il faudrait metre a joure également le fait que la case ne doit plus garder la
position actuelle mais la nouvelle
        Positionnable& operator=(Positionnable&& other) {
            position = std::move(other.position);
            return *this;
        }

        Positionnable (Positionnable&& other) {
            position = std::move(other.position);

        }

*/



    protected :

        // localisation
        Case*  position;

};
/*
class HashWeakPositionnable
{
public :
    size_t operator()(const Positionnable* positionnalbe_ptr) const;
};*/

#endif

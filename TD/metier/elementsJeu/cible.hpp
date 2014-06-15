#ifndef CIBLE
#define CIBLE

#include <iostream>
#include <vector>
#include <SFML/System/Vector2.hpp> // un peu domage d'inclure tout ça pour un vecteur2
#include "positionnable.hpp"
class Case;

class Cible : public Positionnable
{
    public :
        Cible(Case* position,double maxPv,bool pvolante =0, bool pvisible = 1);
        ~Cible () ;

        // geteurs
        virtual double getPV() const                 { return pv;        };
        virtual double getArmure() const             { return armure;    };
        virtual bool isVisible () const { return visible ;};
        virtual bool isVolant () const { return volante ;};

        // seteur
        virtual void setPVactuel(const double p_pv) { if (p_pv > 0) pv = p_pv;}
        virtual void setPVmax(const double p_pvMax) { if (p_pvMax > 0) pvMax = p_pvMax;}
        virtual void setArmure (const double p_armure ) { if (p_armure > 0) armure = p_armure;}

        // gere comment sont subis les dmg, la signature va surement evoluer
        virtual bool subirDommage(double dommage);


        // pour eviter des bugs, soit les implementer, soit les interdire
        Cible& operator=(Cible&& other) = delete;
        Cible (Cible&& other) = delete;
        Cible& operator=(const Cible& other) = delete;
        Cible (const Cible& other) = delete;

        // devrait etre vituelle mais je veux instencier pour des test
        virtual void quitteCase(Case *) { std::cout <<" je suis pas a ma place" << std::endl;} ; // a specifier au niveau de la tour et du monstre
        virtual void arriveCase(Case *){ std::cout <<" Killl meee piiiz" << std::endl;} ;

    protected :
        bool volante;
        bool visible;

        // defence
        double pv;
        double pvMax;
        double armure;




};
#endif


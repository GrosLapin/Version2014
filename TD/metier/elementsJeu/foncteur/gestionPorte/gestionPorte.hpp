#ifndef GESTION_PORTE
#define GESTION_PORTE

#include <vector>
#include <algorithm>
#include <SFML/System/Vector2.hpp>
#include "../../porte/porte.hpp"

class Cible;
class Case;

// classe abstraite definissant le comportement de la gestion de porté generique
/// DANGER : ON NE FAIT PAS DE DIFF TOUR / MOOB pour l'instant IL FAUDRA Y REVENIR

/// NOTE : le liens terrain case est moche mais il nous sert ici

/// NOTE : si probleme de perf, mettre des unodored_set au lieux de certain vector
class GestionPorte
{
    public :
        // on a besoin d'un constructeur pour la porté max
        // GestionPorte() : porteMax(0) {} a voir plus tard


        // parce que j'aiiime les foncteurs
        // la case nous donne aussi le terrain, et ça c'est cool

        virtual std::vector<Cible*> operator() (Case* positionAttaquant);

        // il faut un moyen d'ajouter / enlever une zone de tire
        virtual void addPorte(TypeDePorte forme, int range);
        virtual void removePorte(TypeDePorte forme, int range);

        // les zones d'ombre, pour faire des soustractions de forme
        virtual void addZoneOmbre(TypeDePorte forme, int range);
        virtual void removeZoneOmbre(TypeDePorte forme, int range);

        // pour la reduction de porté eventuelle
        // int getPorteMax(); // a voir plus tard



    protected :
        void majAllZone();
        void majZoneReele();
        virtual void changeCase(Case*);

        Case* dernierePosition; // sert pour eviter de tout recalculer si on a pas changer de place
                                // et comme la majorité des attaquant avec une gestion de porté seront
                                // des tours ça devrait etre utile

        int porteMax;
    /// implementation pour l'instant :
    // à deux liste :
        // porté positive, qui viennent de addPorte
        std::vector<Portee> portePositive;
        // porte negative, qui viennent de removePorte
        std::vector<Portee> porteNegative;

    // une zone virtuelle qui stoque les case si l'attaquant est poseé en 0.0 avec un terrain plein
    // il est recalculé uniquement si on touche aux porté positive ou negative
        std::vector<sf::Vector2<int>> zoneVirtuelle;

    // un conteneur qui stoque les "case a porté reel" c'est a dire l'application des case de la porte
    // sur la position.
    // il est recalculé avec la porté virtuelle si celle si est modifié ou si l'attaquant bouge
        std::vector<Case*> zoneReele;
};

#endif

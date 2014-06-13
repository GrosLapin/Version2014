#ifndef GESTION_PORTE
#define GESTION_PORTE

#include <vector>
#include <algorithm>
#include "../../porte.hpp"

class Cible;

// classe abstraite definissant le comportement de la gestion de porté generique
class GestionPorte
{
    public :
        // on a besoin d'un constructeur pour la porté max
        // GestionPorte() : porteMax(0) {} a voir plus tard


        // parce que j'aiiime les foncteurs
        virtual std::vector<Cible*> operator() (Case* positionAttaquant);

        // il faut un moyen d'ajouter une zone de tire
        /// ATTENTION : Il faut récuperer ce que j'ai deja fait sur les porté de "TD2013"
        virtual void addPorte(int forme, int range)
        {
            portePositive.push_back(Porte(forme,range));
            // La gestion de la porté max est typiquement un truc que je ferais bien en NVI
        }
        virtual void removePorte(int forme, int range)
        {
            portePositive.erase(
             std::find_if(portePositive.begin(),portePositive.end(),[&](Porte& unePorte)
                          { return unePorte.getRange() == range && unePorte.getForme == forme; }
                )
            );
            // La gestion de la porté max est typiquement un truc que je ferais bien en NVI
        }

        /// Question : comment sont stoquer les porté ?
            // - peut on faire de la "soustraction de porté" ?
            // - peut on juste retire une porte qui a deja était mise
        virtual void addZoneOmbre(int forme, int range)
        {
            porteNegative.push_back(Porte(forme,range));
        }
        virtual void removeZoneOmbre(int forme, int range)
        {
            porteNegative.erase(
             std::find_if(portePositive.begin(),portePositive.end(),[&](Porte& unePorte)
                          { return unePorte.getRange() == range && unePorte.getForme == forme; }
                )
            );
            // La gestion de la porté max est typiquement un truc que je ferais bien en NVI
        }
        // pour la reduction de porté eventuelle
        int getPorteMax();

    protected :
        Case* dernierePosition; // sert pour eviter de tout recalculer si on a pas changer de place
                                // et comme la majorité des attaquant avec une gestion de porté seront
                                // des tours ça devrait etre utile

        int porteMax;
    /// implementation pour l'instant :
    // à deux liste :
        // porté positive, qui viennent de addPorte
        std::vector<Porte> portePositive;
        // porte negative, qui viennent de removePorte
        std::vector<Porte> porteNegative;
    // une zone virtuelle qui stoque les case si l'attaquant est poseé en 0.0 avec un terrain plein
    // il est recalculé uniquement si on touche aux porté positive ou negative

    // un conteneur qui stoque les "case a porté reel" c'est a dire l'application des case de la porte
    // sur la position.
    // il est recalculé avec la porté virtuelle si celle si est modifié ou si l'attaquant bouge
};

#endif

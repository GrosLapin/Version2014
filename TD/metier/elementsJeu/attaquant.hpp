#ifndef ATTAQUANT_HPP
#define ATTAQUANT_HPP



#include <stack>
#include <memory>
#include <vector>


#include "positionnable.hpp"

class Cible;
class GestionPorte;
class GestionVision;
class GestionPriorite;
class GestionAttaque;

class Attaquant : public Positionnable
{
    public :


    private : // ou protected, à reflechir

    // stats de base
        double attaquePerSec;
        float dommage;

    // gestion du temps : Soit avec un timer qui lui est propre, soit avec un double qui permet p-e mieux de gerer les depassement
    // il faudrait regarder ce qui coute le moins cher /  plus maintenable
        double tempsAvantAttaque;

    ///Les foncteurs dans leurs odres logique d'application :
    /* on utilisera une pile pour modéliser leur sucession. (Pile de conteneur ou une pile de decorateur en fonction) */
    /** Edit : utiliser un pile ou des décorateur ne permet pas de gerer des cas du stile "pd 30 sec vison plus 1"
        puis 10 sec apres pd 30 sec vison a 50%, comment on "dépile" a la fin du premier bonus ?
    */
    /*
    de plus l'attaquant gere la durée de vie de l'objet, et on doit permetre le poly-morphisme => unique_ptr*/

    // la gestion de la porté, gere la forme, la longeur de la porté, mais également des effets plus funky du genre
    // 50% de visibilité ext
        std::vector<std::unique_ptr<GestionPorte>> pileGestionPorte;

    // la gestion de la vision : monstre normal, anty piaf, invisible, combinaison ext
        std::vector<std::unique_ptr<GestionVision>> pileGestionVision;

    // la gestion de la priorité, le choix de la cible, tri le tableau de cible en fonction des prefs interne
    // => focus / plus ou moins de pv ext
        std::vector<std::unique_ptr<GestionPriorite>> pileGestionPriorite;

    // gestion de l'attaque : permet de gere l'attaque en zone et cible multyple
        std::vector<std::unique_ptr<GestionAttaque>> pileGestionAttaque;
};


#endif

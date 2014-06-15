#include "gestionPorte.hpp"
#include "../../porte/porte.hpp"
#include "../../../terrain/case.hpp"
#include "../../../terrain/terrain.hpp"

void GestionPorte::addPorte(TypeDePorte forme, int range)
{
    // note La gestion de la porté max est typiquement un truc que je ferais bien en NVI
    portePositive.push_back(Portee(forme,range));

    // on met a jours "stupidement" la zoneVirtuelle car on peut pas le faire incrementalement à
    // cause
    majAllZone ();
}

void GestionPorte::removePorte(TypeDePorte forme, int range)
{
    // on supprime uniquement si on trouve une porté qui match bien
    auto it = std::find_if(portePositive.begin(),portePositive.end(),[&](Portee& unePorte)
                            { return unePorte.getRange() == range && unePorte.getForme() == forme; }
                          );
    if ( it != portePositive.end() )
    {
        portePositive.erase(it);
        // idem
        majAllZone ();
    }
}

void GestionPorte::addZoneOmbre(TypeDePorte forme, int range)
{
    porteNegative.push_back(Portee(forme,range));
    // on met a jours "stupidement" la zoneVirtuelle car on peut pas le faire incrementalement à
    // cause
    majAllZone ();
}

void GestionPorte::removeZoneOmbre(TypeDePorte forme, int range)
{
    auto it = std::find_if(porteNegative.begin(),porteNegative.end(),[&](Portee& unePorte)
                            { return unePorte.getRange() == range && unePorte.getForme() == forme; }
                          );
    if ( it != porteNegative.end() )
    {
        porteNegative.erase(it);
        // idem
        majAllZone ();
    }
}

void GestionPorte::majAllZone()
{
    // 1) on clean les zones
    zoneVirtuelle.clear();

    // 2) on ajoute le positif
    for (Portee& unePorte : portePositive)
    {
        // on recupere les case virtuelles de chaque porte
        std::vector<sf::Vector2<int>> listCaseXY = unePorte.getZoneVirturelle();
        for (sf::Vector2<int>& uneCaseXY : listCaseXY )
        {
            // on l'ajoute que si elle n'est pas deja dans la liste
            auto it = std::find(zoneVirtuelle.begin(),zoneVirtuelle.end(),uneCaseXY); // find utilise l'operator == qui existe entre les vector2 donc c'est ok
            if ( it == zoneVirtuelle.end() )
            {
                // si on a pas trouvé
                zoneVirtuelle.push_back(uneCaseXY);
            }
        }
    }

    // 3) on retire ce qu'on à retirer
    for (Portee& unePorte : porteNegative)
    {
        // on recupere les case virtuelles de chaque porte
        std::vector<sf::Vector2<int>> listCaseXY = unePorte.getZoneVirturelle();
        for (sf::Vector2<int>& uneCaseXY : listCaseXY )
        {
            // on delete si on trouve
            auto it = std::find(zoneVirtuelle.begin(),zoneVirtuelle.end(),uneCaseXY); // find utilise l'operator == qui existe entre les vector2 donc c'est ok
            if ( it != zoneVirtuelle.end() )
            {
                // Si on a trouvé, DESTROYYYY !!
                zoneVirtuelle.erase(it);
            }
        }
    }

    //4) GG, la zone virtuelle est a jour, now la zone réele
    majZoneReele();
}

void GestionPorte::majZoneReele()
{
    // on veut juste faire le mapping entre la zone virtuelle et la position de l'attaquant
    // 1) on clear
    zoneReele.clear();

    // 1.5) (xD) on verifie qu'on peut le calculer :  il nous faut une case :) (valide)
    if (nullptr != dernierePosition && nullptr != dernierePosition->getTerrain() )
    {
        // 2) on ajoute,
        Terrain laMap = *(dernierePosition->getTerrain());
        Case laPosition = * (dernierePosition);
        for (sf::Vector2<int>& uneCaseXY : zoneVirtuelle)
        {
            Case* uneCase = laMap.getCase(laPosition.getI()+uneCaseXY.x,laPosition.getJ()+uneCaseXY.y);
            if ( nullptr != uneCase )
            {
                zoneReele.push_back(uneCase);
            }
        }
    }


}

void GestionPorte::changeCase(Case* newCase)
{
    dernierePosition = newCase;
    majZoneReele();
}

std::vector<Cible*> GestionPorte::operator() (Case* positionAttaquant)
{
    // si on a pas changer, on recalcule pas
    if ( dernierePosition != positionAttaquant)
    {
        changeCase(positionAttaquant);
    }

    std::vector<Cible*> vectCible;
    // on regarde les cibles dans la zone reele
    for (Case* uneCase : zoneReele )
    {
        vectCible.insert(vectCible.end(),uneCase->getCible().begin(),uneCase->getCible().end());
    }

    // et on retourne le tout
    return vectCible;
}



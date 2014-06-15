#include "porte.hpp"

Portee::Portee (TypeDePorte forme, int range)
{
    // le centre
    sf::Vector2<int> centre;
    centre.x = 0;
    centre.y = 0;

    switch (forme)
    {
        case Disque :
        {
            // il faut le centre
            zoneVirtuelle.push_back(centre);

            // les cercles concentriques
            for (int i = 1; i <= range ; i++ )
            {
                std::vector<sf::Vector2<int> > cercle = calculCercle(i);
                for ( sf::Vector2<int>& uneCase : cercle )
                {
                    zoneVirtuelle.push_back(uneCase);
                }
            }
            break;
        }
        case Etoile :
        {
             // il faut le centre
            zoneVirtuelle.push_back(centre);

            for (int i = 1; i <= range ; i++ )
            {
                // les 6 points principaux
                sf::Vector2<int> XYest ;
                XYest.x = centre.x + i;
                XYest.y = centre.y;

                sf::Vector2<int> XYouest ;
                XYouest.x = centre.x - i;
                XYouest.y = centre.y;

                sf::Vector2<int> XYsud_ouest ;
                XYsud_ouest.x = centre.x - i;
                XYsud_ouest.y = centre.y + i ;

                sf::Vector2<int> XYnord_ouest ;
                XYnord_ouest.x = centre.x ;
                XYnord_ouest.y = centre.y - i ;

                sf::Vector2<int> XYnord_est ;
                XYnord_est.x = centre.x + i;
                XYnord_est.y = centre.y - i;

                sf::Vector2<int> XYsud_est ;
                XYsud_est.x = centre.x;
                XYsud_est.y = centre.y + i;


                zoneVirtuelle.push_back(XYest);
                zoneVirtuelle.push_back(XYnord_est);
                zoneVirtuelle.push_back(XYnord_ouest);
                zoneVirtuelle.push_back(XYouest);
                zoneVirtuelle.push_back(XYsud_ouest);
                zoneVirtuelle.push_back(XYsud_est);
            }
            break;
        }
        case LigneO_E :
        {
             // il faut le centre
            zoneVirtuelle.push_back(centre);

            for (int i = 1; i <= range ; i++ )
            {
                // EST - OUEST
                sf::Vector2<int> XYest ;
                XYest.x = centre.x + i;
                XYest.y = centre.y;

                sf::Vector2<int> XYouest ;
                XYouest.x = centre.x - i;
                XYouest.y = centre.y;

                zoneVirtuelle.push_back(XYest);
                zoneVirtuelle.push_back(XYouest);

            }
            break;
        }
        case LigneSO_NE:
        {
             // il faut le centre
            zoneVirtuelle.push_back(centre);

            for (int i = 1; i <= range ; i++ )
            {
                // NO - SO

                sf::Vector2<int> XYsud_ouest ;
                XYsud_ouest.x = centre.x - i;
                XYsud_ouest.y = centre.y + i ;

                sf::Vector2<int> XYnord_est ;
                XYnord_est.x = centre.x + i;
                XYnord_est.y = centre.y - i;
                sf::Vector2<int> XYsud_est ;

                zoneVirtuelle.push_back(XYnord_est);
                zoneVirtuelle.push_back(XYsud_ouest);
            }
            break;
        }
        case LigneSE_NO :
        {
             // il faut le centre
            zoneVirtuelle.push_back(centre);

            for (int i = 1; i <= range ; i++ )
            {
                sf::Vector2<int> XYnord_ouest ;
                XYnord_ouest.x = centre.x ;
                XYnord_ouest.y = centre.y - i ;

                sf::Vector2<int> XYsud_est ;
                XYsud_est.x = centre.x;
                XYsud_est.y = centre.y + i;

                zoneVirtuelle.push_back(XYnord_ouest);
                zoneVirtuelle.push_back(XYsud_est);
            }

            break;
        }
        case CerclePaire :
        {
            // 0 = le centre 2 / 4 ...
            // il faut le centre
            zoneVirtuelle.push_back(centre);

            // les cercles concentriques
            for (int i = 2; i <= range ; i += 2 )
            {
                std::vector<sf::Vector2<int> > cercle = calculCercle(i);
                // on ajoute le cercle au disque
                for (sf::Vector2<int>& uneCase : cercle)
                {
                    zoneVirtuelle.push_back(uneCase);
                }
            }
            break;
        }
        case CercleImpaire :
        {
            // il y a pas le centre : 1/3/5/7
            // les cercles concentriques
            for (int i = 1; i <= range ; i += 2 )
            {
                std::vector<sf::Vector2<int> > cercle = calculCercle(i);
                for (sf::Vector2<int>& uneCase : cercle)
                {
                    zoneVirtuelle.push_back(uneCase);
                }
            }
            break;
        }
    }

}


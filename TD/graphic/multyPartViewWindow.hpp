#ifndef MULTPARTVIEWWINDOW_HPP
#define MULTPARTVIEWWINDOW_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>


struct ElementWindow
{
    // connaitre la taille en hauteur et en largeur de rectangle
    std::string nom;
    sf::Vector2<double> pourCentTaille, pourCentCoordonnee;

    ElementWindow (std::string p_nom,sf::Vector2<double> p_pourCentTaille,
                   sf::Vector2<double> p_pourCentCoordonnee)
    :nom(p_nom),
    pourCentTaille(p_pourCentTaille),
    pourCentCoordonnee(p_pourCentCoordonnee)
    {}
    bool operator< (const ElementWindow&  autre) const
    {
        return nom < autre.nom;
    }
};

// déclaration de constante, j'aurais aimé une enum mais je peux pas faire une enum de class en c++11
class EnumElementsWindow
{
    public :
        static ElementWindow Jeu,Menu;
};
ElementWindow EnumElementsWindow::Jeu ("Jeu",sf::Vector2<double> (0.75f,1),sf::Vector2<double> (0,0));
ElementWindow EnumElementsWindow::Menu("Menu",sf::Vector2<double> (0.25f,1),sf::Vector2<double> (0.75f,0));

enum class OriginCoordinate
{
    Center,Top
};

class MultyPartViewWindow
{
    //// DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
    //// DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
    //// DANGER DANGER                                                                                                   DANGER DANGER
    //// DANGER DANGER                                                                                                   DANGER DANGER
    //// DANGER DANGER                         la taille dans multypartvielw window n'est pas la taille de               DANGER DANGER
    //// DANGER DANGER                                        la fenetre si on redimention a la main!!                   DANGER DANGER
    //// DANGER DANGER                                                                                                   DANGER DANGER
    //// DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
    //// DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER


    std::map<ElementWindow,sf::View> mapElemFenetre;
    int largeur = 400 ,hauteur = 400,cote = 40 ,zoom = 1;
    std::string nom;
    sf::RenderWindow window;

public :

    sf::Vector2f getCursorInView (ElementWindow view, sf::Vector2i cursorInWindow)
    {
        window.setView(mapElemFenetre[view]);
        return window.mapPixelToCoords(cursorInWindow);
    }
    sf::RectangleShape getRectangleView (ElementWindow view)
    {
        // on défini un rectangle de la taille de la fene
        sf::RectangleShape retour(sf::Vector2f(view.pourCentTaille.x*largeur,view.pourCentTaille.y*hauteur));
        retour.setPosition(sf::Vector2f(view.pourCentCoordonnee.x*largeur,view.pourCentCoordonnee.y*hauteur));
        return retour;
    }
    int getCote() { return cote;}
    void addView (ElementWindow element, OriginCoordinate orgine, int zoom)// sf::Vector2f rectangle)
    {
       /* sf::View vue (  sf::Vector2f(rectangle.x,rectangle.y),
                        sf::Vector2f((rectangle.x*cote/zoom)/2,(rectangle.y*cote/zoom)/2)
                    );*/

                 /*sf::View vue (  sf::Vector2f(0,0),
                        sf::Vector2f((rectangle.x)/2,(rectangle.y)/2)
                    );*/

        if ( orgine == OriginCoordinate::Center)
        {
            sf::View vue (
                        sf::Vector2f(0,0),
                        sf::Vector2f(   element.pourCentTaille.x*largeur*zoom,
                                        element.pourCentTaille.y*hauteur*zoom
                                    )
                        );

            vue.setViewport(sf::FloatRect( element.pourCentCoordonnee.x,
                                        element.pourCentCoordonnee.y,
                                        element.pourCentTaille.x,
                                        element.pourCentTaille.y
                                      ));

            mapElemFenetre.insert(std::pair<ElementWindow,sf::View>(element,std::move(vue)));
        }
        if ( orgine == OriginCoordinate::Top )
        {
            sf::View vue (
                        sf::Vector2f(0+element.pourCentTaille.x*largeur/2,0+element.pourCentTaille.y*hauteur/2),
                        sf::Vector2f(   element.pourCentTaille.x*largeur*zoom,
                                        element.pourCentTaille.y*hauteur*zoom
                                    )
                        );

            vue.setViewport(sf::FloatRect( element.pourCentCoordonnee.x,
                                        element.pourCentCoordonnee.y,
                                        element.pourCentTaille.x,
                                        element.pourCentTaille.y
                                      ));

            mapElemFenetre.insert(std::pair<ElementWindow,sf::View>(element,std::move(vue)));
        }

    }

    // en valeur absolue ( genre 50 62 1 2)
    void draw (sf::Drawable& drawable, ElementWindow& zoneDessin)
    {
        window.setView(mapElemFenetre[zoneDessin]);
        window.draw(drawable);
    }

    // en pourcentage de la vue
    void perCentToFix (sf::RectangleShape& rec, ElementWindow& zoneDessin)
    {
        rec.setSize(sf::Vector2f(zoneDessin.pourCentTaille.x*largeur*rec.getSize().x,zoneDessin.pourCentTaille.y*rec.getSize().y*hauteur));
        rec.setPosition(sf::Vector2f(zoneDessin.pourCentTaille.x*largeur*rec.getPosition().x,zoneDessin.pourCentTaille.y*rec.getPosition().y*hauteur));
    }

    MultyPartViewWindow (std::string titre = "oui oui")  : nom(titre), window(sf::VideoMode(largeur, hauteur), nom){}
    MultyPartViewWindow (int largeur_p ,int hauteur_p, std::string titre = "oui oui")  :
        largeur(largeur_p),
        hauteur(hauteur_p),
        nom(titre),
        window(sf::VideoMode(largeur, hauteur),nom)
        {}

    sf::RenderWindow& getWindow() { return window;}
    sf::View& getView (ElementWindow elem) { return mapElemFenetre[elem];}
};

#endif // MULTPARTVIEWWINDOW_HPP

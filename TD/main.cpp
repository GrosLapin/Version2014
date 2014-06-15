#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <string> // pour le to_string... mais ça marche pas merci 4.7.1
#include <algorithm>


#include "graphic/fonctionGraphique.hpp"
#include "graphic/deplacementCamera.hpp"
#include "graphic/multyPartViewWindow.hpp"
#include "metier/terrain/terrain.hpp"
#include "metier/terrain/case.hpp"
#include "metier/elementsJeu/positionnable.hpp"
#include "tools/utilitaire.hpp"
#include "metier/elementsJeu/cible.hpp"
using namespace std;

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/ring.hpp>


BOOST_GEOMETRY_REGISTER_POINT_2D(sf::Vector2f, float, cs::cartesian, x, y) ;
BOOST_GEOMETRY_REGISTER_POINT_2D(sf::Vector2i, int, cs::cartesian, x, y) ;
BOOST_GEOMETRY_REGISTER_RING(std::vector<sf::Vector2f>);



int main( int argc, char *argv[])
{

    // il a sans doute un truc a faire pour que j'ai pas a calculer de tete le ratio ( la réponse est pas "prend une calc connard" )
    MultyPartViewWindow window (800,600,"it's gonna work, bitch !");
    window.addView(EnumElementsWindow::Jeu  , OriginCoordinate::Center,2);
    window.addView(EnumElementsWindow::Menu , OriginCoordinate::Top,1);


    // le timer global
    sf::Clock timerFix;

    // on récupere le dossier
    std::string dossier =  getDossier(argv[0]);
    std::string fichier = "map.map";

    // chargement de la police d'ecriture
    sf::Font MyFont;
    if (!MyFont.loadFromFile(dossier+"arial.ttf")) { std::cerr << "arial not found" << std::endl; }
    sf::Text text;
    text.setFont(MyFont);
    text.setCharacterSize(20);
    text.setColor(sf::Color::Red);

    // les indications visuelle : case porté sourie...
    sf::ConvexShape polygon = createHexagone (window.getCote(), sf::Color(255, 255, 255,245));
    sf::ConvexShape polygonBleu = createHexagone (window.getCote(), sf::Color(0, 0, 255,80));

    Terrain terrain = loadMap(dossier+fichier);

    // on gere les touches en gerant le zoom
    DeplacementCamera gestionTouches(1,1);

    // les ring pour le calcul d'hover (si il y a pas de redimentionnement ça pourrait rester la mais bon...)
    auto ringWindow = getRing(window.getWindow()) ;
    auto ringView = getRing(window.getRectangleView(EnumElementsWindow::Jeu)) ;
    sf::Vector2i cursorInWindow = sf::Mouse::getPosition(window.getWindow());
    sf::Vector2f cursorInView = window.getCursorInView(EnumElementsWindow::Jeu,  cursorInWindow);

    /// la gestion des touches sur le coté (pas tres beau c'est juste pour se souvenir qu'on a un menu ici)
    // le fond du menu
    sf::RectangleShape fondView(sf::Vector2f(1,1)) ;
    window.perCentToFix(fondView, EnumElementsWindow::Menu);
    fondView.setFillColor(sf::Color(127,127,127)) ;
    // un bouton
    sf::RectangleShape bouton1(sf::Vector2f(1,0.1)) ;
    window.perCentToFix(bouton1, EnumElementsWindow::Menu);
    sf::Color bouton1couleur(0,127,127);
    // un autre bouton :o
    sf::RectangleShape bouton2(sf::Vector2f(1,0.1)) ;
    bouton2.setPosition(0,0.1);
    window.perCentToFix(bouton2, EnumElementsWindow::Menu);
    sf::Color bouton2couleur(127,127,0);
    // la couleur a ajouter quand on est en hover
    sf::Color overColor(18,18,18);


    // temporaire, normalement positionable devrait etre abs
    vector<unique_ptr<Cible>> vectConstruct;

    while (window.getWindow().isOpen())
    {

        // gestion de la vue
         gestionTouches (window.getView(EnumElementsWindow::Jeu),timerFix);
         ringWindow = getRing(window.getWindow()) ;
         ringView = getRing(window.getRectangleView(EnumElementsWindow::Jeu)) ;


        /// DANGER !! Il faudrait reflechier ou restart le timer et ce que ça implique
        timerFix.restart();

        // récupération de la position de la souris dans la fenêtre
         cursorInWindow = sf::Mouse::getPosition(window.getWindow());
         cursorInView = window.getCursorInView(EnumElementsWindow::Jeu,  cursorInWindow);

        // Clear screen
        if ( !boost::geometry::disjoint(ringView, cursorInWindow) )
            window.getWindow().clear(sf::Color::Magenta);
        else
            window.getWindow().clear(sf::Color::Black);


        placePositionableIJ ( -5 , -5, polygonBleu,  window.getCote());
        //gestionTouches.imuable(polygonBleu);
        window.draw(polygonBleu,EnumElementsWindow::Jeu);





        sf::Vector2<int> caseSelection = mouseToXY(cursorInView.x, cursorInView.y, window.getCote());
        sf::Vector2<int> ijSelection = XYtoIJ( caseSelection, window.getCote() );



        // couleur des boutons

        bouton2.setFillColor(bouton2couleur) ;
        bouton1.setFillColor(bouton1couleur) ;
        cursorInView = window.getCursorInView(EnumElementsWindow::Menu,  cursorInWindow);
        if ( ! boost::geometry::disjoint(cursorInView,getRing(bouton1)))
                {
                    bouton1.setFillColor(overColor+bouton1couleur) ;

                }
                if ( ! boost::geometry::disjoint(cursorInView,getRing(bouton2)))
                {
                   bouton2.setFillColor(overColor+bouton2couleur) ;

                }
        // boucle event
        sf::Event event;

        while (window.getWindow().pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                // semble buger
                saveMap(terrain,fichier);
                window.getWindow().close();
            }
            if (event.type == sf::Event::MouseButtonReleased )
            {
                cursorInView = window.getCursorInView(EnumElementsWindow::Menu,  cursorInWindow);

                if ( ! boost::geometry::disjoint(cursorInView,getRing(bouton1)))
                {

                    cout << "bouton 1";
                }
                if ( ! boost::geometry::disjoint(cursorInView,getRing(bouton2)))
                {

                   cout << "bouton2";
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // si on est sur un case connue du terrain
                    if ( nullptr != terrain.getCase(ijSelection.x,ijSelection.y) )
                    {
                        std::cout << terrain.getCase(ijSelection.x,ijSelection.y) <<endl;
                        vectConstruct.push_back(unique_ptr<Cible>(new Cible(terrain.getCase(ijSelection.x,ijSelection.y),100)));
                        std::cout << "__" <<  vectConstruct.size() << "__";
                    }
                }
            }


        }
        if ( sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if ( vectConstruct.size() > 0)
                vectConstruct.erase(vectConstruct.begin());
        }

        // affichage de la map
        for ( Case& caseRef : terrain )
        {
            // affichage des case
            placePositionableIJ ( caseRef.getI() ,  caseRef.getJ() , polygon,  window.getCote());
            window.draw(polygon,EnumElementsWindow::Jeu);


            text.setString(patch::to_string(caseRef.getI())+","+patch::to_string(caseRef.getJ()));
            placePositionableIJ ( caseRef.getI() ,caseRef.getJ() , text,  window.getCote());
            window.draw(text,EnumElementsWindow::Jeu);
        }

        for (auto &positio : vectConstruct )
        {
            Case* uneCase =  positio->getPosition();
            if ( nullptr != uneCase )
            {
                 placePositionableIJ ( uneCase->getI() , uneCase->getJ() , polygonBleu,  window.getCote());
                window.draw(polygonBleu,EnumElementsWindow::Jeu);
            }

        }
        int cpt = 0;
        for (Case& uneCase : terrain )
        {
            if ( uneCase.getOccupe() )
                cpt++;
        }

        // placePositionableIJ ( ijSelection.x ,ijSelection.y, *PolygonRose, cote, offSetX,  offSetY);
        //app.draw(*PolygonRose);


        window.draw(fondView,EnumElementsWindow::Menu);
        window.draw(bouton1,EnumElementsWindow::Menu);
        window.draw(bouton2,EnumElementsWindow::Menu);



        window.getWindow().display();


    }
    return 0;
}


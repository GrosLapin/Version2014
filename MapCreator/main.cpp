#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <string> // pour le to_string... mais ça marche pas merci 4.7.1
#include "../TD/graphic/fonctionGraphique.hpp"
#include "../TD/graphic/deplacementCamera.hpp"
#include "../TD/tools/utilitaire.hpp"
#include "../TD/graphic/multyPartViewWindow.hpp"
#include "../TD/metier/terrain/terrain.hpp"
#include "../TD/metier/terrain/case.hpp"

using namespace std;

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/ring.hpp>


BOOST_GEOMETRY_REGISTER_POINT_2D(sf::Vector2f, float, cs::cartesian, x, y) ;
BOOST_GEOMETRY_REGISTER_POINT_2D(sf::Vector2i, int, cs::cartesian, x, y) ;
BOOST_GEOMETRY_REGISTER_RING(std::vector<sf::Vector2f>);



int main( int argc, char *argv[])
{

    int a ;
    std::cout << &a ;



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



    Terrain terrain;
    loadMap(terrain,fichier);

    DeplacementCamera gestionTouches(1,1);
 // on change la valeur du cursor quand on gere le menu


        auto ringWindow = getRing(window.getWindow()) ;
        auto ringView = getRing(window.getRectangleView(EnumElementsWindow::Jeu)) ;
        sf::Vector2i cursorInWindow = sf::Mouse::getPosition(window.getWindow());
        sf::Vector2f cursorInView = window.getCursorInView(EnumElementsWindow::Jeu,  cursorInWindow);



        sf::RectangleShape fondView(sf::Vector2f(1,1)) ;
        window.perCentToFix(fondView, EnumElementsWindow::Menu);
        fondView.setFillColor(sf::Color(127,127,127)) ;

        sf::Color overColor(18,18,18);


        sf::RectangleShape bouton1(sf::Vector2f(1,0.1)) ;
        window.perCentToFix(bouton1, EnumElementsWindow::Menu);
        sf::Color bouton1couleur(0,127,127);



        sf::RectangleShape bouton2(sf::Vector2f(1,0.1)) ;
        bouton2.setPosition(0,0.1);
        window.perCentToFix(bouton2, EnumElementsWindow::Menu);
        sf::Color bouton2couleur(127,127,0);


        cout << bouton2.getPoint(0) << "  "
         <<bouton2.getPoint(1) << "  "
         <<bouton2.getPoint(2) << "  "
         << bouton2.getPoint(3)  << "    " <<  getAllPoints(bouton2) <<endl;



        string m_saisie;
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
            if (event.type == sf::Event::TextEntered)
            {

                if ((event.text.unicode > 30 && (event.text.unicode < 127 || event.text.unicode > 159)))
                {
                    m_saisie += static_cast<char>(event.text.unicode);
                }
            }

            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
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
        }
        if ( sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if ( !boost::geometry::disjoint(ringView, cursorInWindow) )
                terrain.addCase(ijSelection.x,ijSelection.y);
        }
        else if ( sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            terrain.removeCase(ijSelection.x,ijSelection.y);
        }
        // affichage de la map

        cout << m_saisie <<std::endl;
        for ( auto &sharded_ptr : terrain )
        {
            // affichage des case
            placePositionableIJ ( sharded_ptr.get()->getI() ,  sharded_ptr.get()->getJ() , polygon,  window.getCote());
            window.draw(polygon,EnumElementsWindow::Jeu);


            text.setString(patch::to_string(sharded_ptr.get()->getI())+","+patch::to_string(sharded_ptr.get()->getJ()));
            placePositionableIJ ( sharded_ptr.get()->getI() ,sharded_ptr.get()->getJ() , text,  window.getCote());
            window.draw(text,EnumElementsWindow::Jeu);



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

/*
 //Pour les archives ( et pour le cas ou vraiment j'ai chier xD
int main( int argc, char *argv[])
{

    // parametre de la grille
    int cote = 40;
    int zoom = 5;
    int offSetX =400,offSetY = 400;
   // MultyPartViewWindow test;
    sf::Clock timerFix;

    // on récupere le dossier

    std::string dossier =  getDossier(argv[0]);

     // Create main window
    sf::RenderWindow app(sf::VideoMode(offSetX*2, offSetY*2), "Toujours pas fini ? Oo");


    double pourCentLargeur = 0.75;
    sf::Vector2f Center     (offSetX                ,offSetY);
    sf::Vector2f HalfSize   ((offSetX*cote/zoom)*pourCentLargeur/2  ,(offSetY*cote/zoom)/2);
    sf::View view           (Center                 ,HalfSize);
    view.setViewport(sf::FloatRect(0.0f, 0.0f, pourCentLargeur, 1.0f)) ;

    sf::Vector2f rightSize(offSetX*2,offSetX*2) ;
    sf::Vector2f origin(10, 10) ;
    sf::Vector2f rectangle(50,50);

    sf::View test(
                                                 sf::Vector2f(origin.x+rectangle.x/2,origin.y+rectangle.y/2),
                                                 sf::Vector2f(rectangle.x,rectangle.y)
                                                 );

    sf::View rightView( sf::FloatRect(origin, rightSize) ) ;

    rightView.setViewport(sf::FloatRect(pourCentLargeur, 0.0f, 1-pourCentLargeur, 1.0f)) ;

    // chargement de la police d'ecriture
    sf::Font MyFont;
    if (!MyFont.loadFromFile(dossier+"arial.ttf"))  std::cerr << "arial not found" << std::endl;
    sf::Text *Text = new sf::Text();
    Text->setFont(MyFont);
    Text->setCharacterSize(20);
    Text->setColor(sf::Color::Red);

    ///TODO : a mort les vilains pointeur
    // les indications visuelle : case et porté
    //sf::Shape& Polygon ( createHexagone (cote, sf::Color(255, 255, 255,245)));


    sf::ConvexShape Polygon = createHexagone (cote, sf::Color(255, 255, 255,245));
    sf::ConvexShape PolygonBleu = createHexagone (cote, sf::Color(0, 0, 255,80));

    vector<pair<int,int>> speudoMap;
    speudoMap.emplace_back(0,0);
    speudoMap.emplace_back(1,0);
    speudoMap.emplace_back(2,0);
    speudoMap.emplace_back(3,3);
    speudoMap.emplace_back(5,-5);

    DeplacementCamera gestionTouches(1,1);


    while (app.isOpen())
    {

        // gestion de la vue
        gestionTouches (view,timerFix);


        /// DANGER !! Il faudrait reflechier ou restart le timer et ce que ça implique
        timerFix.restart();

        // Clear screen
        app.clear(sf::Color::Black);

        // on met un vue
        app.setView(view);
        placePositionableIJ ( -5 , -5, PolygonBleu, cote, offSetX,  offSetY);
        //gestionTouches.imuable(PolygonBleu);
        app.draw(PolygonBleu);







        // récupération de la position de la souris dans la fenêtre
        sf::Vector2i cursorInWindow = sf::Mouse::getPosition(app);
        sf::Vector2f cursorInView = app.mapPixelToCoords(cursorInWindow);

   cout << cursorInWindow << "   "<< cursorInView << endl;
        sf::Vector2<int> caseSelection = mouseToXY(cursorInView.x, cursorInView.y,  cote,  offSetX, offSetX);
        sf::Vector2<int> ijSelection = XYtoIJ( caseSelection,cote,offSetX,offSetY );

        //cout << cursorInWindow ;
        // boucle event
        sf::Event event;

        while (app.pollEvent(event))
        {

            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }



        }
        if ( sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
             speudoMap.emplace_back(ijSelection.x,ijSelection.y);
        }
        else if ( sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            auto it = find(speudoMap.begin(),speudoMap.end(),pair<int,int>(ijSelection.x,ijSelection.y));
            if (   it != speudoMap.end() )
            {
                 speudoMap.erase(it);
            }

        }

        // affichage de la map


        for ( auto &unePaire : speudoMap )
        {
            // affichage des case
            placePositionableIJ ( unePaire.first , unePaire.second , Polygon, cote, offSetX,  offSetY);
            app.draw(Polygon);


            Text->setString(patch::to_string(unePaire.first)+","+patch::to_string(unePaire.second));
            placePositionableIJ ( unePaire.first , unePaire.second , *Text, cote, offSetX,  offSetY);
            app.draw(*Text);

        }

        // placePositionableIJ ( ijSelection.x ,ijSelection.y, *PolygonRose, cote, offSetX,  offSetY);
        //app.draw(*PolygonRose);


{

        sf::RectangleShape rect(sf::Vector2f(50,50)) ;
        rect.setPosition(20,20) ;
        rect.setFillColor(sf::Color::Red) ;
        app.draw(rect) ;
}
        app.setView(test) ;
        sf::RectangleShape rect(sf::Vector2f(1,1)) ;
        rect.setPosition(10,10) ;
        rect.setFillColor(sf::Color(0,0,127)) ;
        app.draw(rect) ;


         cursorInWindow = sf::Mouse::getPosition(app);
        cursorInView = app.mapPixelToCoords(cursorInWindow);



       // cout << test.getSize() << " _ "<< test.getCenter() << endl;

        app.display();


    }
    return 0;
}
*/


#ifndef DEPLACEMENT_CAMERA_HPP
#define DEPLACEMENT_CAMERA_HPP
#include <SFML/Graphics.hpp>

class DeplacementCamera{

    double scaleZoom;
    double vitesseDeplacement;
    int ratioZoom;
    double offset;
    public :
        DeplacementCamera(double scale = 1,double vitesse = 0.5) : scaleZoom(scale), vitesseDeplacement (vitesse),ratioZoom(1000)
        {}
        void operator()(sf::View &View, sf::Clock &timer);
        void imuable (sf::Shape& shape);
        // set / get
        double getScaleZoom () { return scaleZoom;}
        void   setScaleZoom (double zoom) { if ( zoom > 0) { scaleZoom = zoom;}}
        double getVitesseDeplacement () { return vitesseDeplacement;}
        void   setVitesseDeplacement (double vitesse) { if ( vitesse > 0) { vitesseDeplacement = vitesse;}}
};



#endif // DEPLACEMENT_CAMERA_HPP


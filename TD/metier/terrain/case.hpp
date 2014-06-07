#ifndef CASE_HPP
#define CASE_HPP

#include <cstddef>
#include <vector>
#include <list>
#include <set>
#include <sstream>
#include <functional>
#include <array>
#include <unordered_map>
#include <map>
#include <memory>
#include <unordered_set>
#include <iostream>


#include "enumTerrain.hpp"
#include "../elementsJeu/positionnable.hpp"
#include "../../tools/structAndOperator.hpp"
// il va faloir gerer les voisin comme des weak-ptr
class Case : public std::enable_shared_from_this<Case>
{
    public :
        Case(int p_i, int p_j);
        Case();

        ~ Case();

        int getI () const { return i;};
        int getJ () const { return j;};

        std::string toString() const;

        bool operator==(const Case& other) const
        {
            return ( i == other.i ) && (j == other.j ) ;
        }

        // pour la navigation dans la map
        bool quelleDirection(const Case& p_voisin,Direction &out_dir) ;
        std::weak_ptr<Case> getVoisin(const Direction& direction);

        // pour l'editeur de map
        void addVoisin(const Direction& direction,std::weak_ptr<Case>  p_voisin);


        void addPositionnable (std::weak_ptr<Positionnable> &wkp_pos)
        {
             std::cout << "la \n";
            setPositionable.insert(wkp_pos);
        }


        // les assesseurs sur les booléen
        bool isFranchissable   () const    { return (setPositionable.size() == 0 );}
        bool getOccupe          () const    { return occupe;};
        void setOccupe          (bool boule){ occupe = boule;};

    private :
        // la definition meme d'un case
        int i,j;
        //std::map<Direction,std::reference_wrapper<Case>> voisin; //Case* voisin[6]; std::reference_wrapper<Case>
        std::array<std::weak_ptr<Case>,6> voisin;
        std::unordered_set<std::weak_ptr<Positionnable>, HashWeakPositionnable> setPositionable;
        bool franchissable;
        bool occupe;



        /*
        // utile pour les sort de zone ( si si )
        std::set<Monstre* > listeMonstre;
        // liste de tours
        std::set<Constructible* >   listeConstructible;

        // la lsite des effect sur la case
        std::list<Effet* > listEffets;


        // la gestion de la liste de monstre
        void monstreArrive  (Monstre* moob);
        void monstrePart    (Monstre* moob);
        std::set<Monstre* > getListMonstre() { return listeMonstre;};

        // la gestion des tours a portée
        void ajoutConstructible      (Constructible* p_tour);
        void suppressionConstructible(Constructible* p_tour);
        std::set<Constructible* >    getListConstructible()    { return listeConstructible;};


        // gestion de Effect
        void ajoutEffect    (Effet * p_Effect);
        void removeEffect   (Effet * p_Effect);
        std::list<Effet* > getListEffets() const { return listEffets;};
        template <class T> void ajoutEffect    (std::vector<T> &p_listEffect)
        {
            // ajoute de tout les effect dans la liste
            typename std::vector<T>::iterator it = p_listEffect.begin();

            for ( it ; it != p_listEffect.end() ; ++it )
            {
                ajoutEffect((*it));
            }
        };
        template <class T> void removeEffect   (std::vector<T> &p_listEffect)
        {
            // on supprime la liste des effet qu'on nous demande de supprimer

            typename std::vector<T>::iterator it = p_listEffect.begin();
            for ( it ; it != p_listEffect.end() ; ++it )
            {
                removeEffect((*it));
            }
        };

        // pour le debug
        int nbCible () { return listeMonstre.size() + listeConstructible.size(); };
        */
};


#endif



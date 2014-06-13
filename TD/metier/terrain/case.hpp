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
class Case
{

    public :
        Case(int p_i, int p_j);
        Case();

        ~ Case();

        int getI () const { return i;};
        int getJ () const { return j;};

        std::string toString() const;

        // l'égalité se base sur l'égalité des indices
        bool operator==(const Case& other) const
        {
            return ( i == other.i ) && (j == other.j ) ;
        }

        // pour la navigation dans la map
        bool quelleDirection(const Case* p_voisin,Direction &out_dir) ;
        Case* getVoisin(const Direction& direction);

        // pour l'editeur de map et le constructeur de terrain
        void addVoisin(const Direction& direction,Case*  p_voisin);
        void removeVoisin(const Direction& direction);


        void addPositionnable (Positionnable* pos_ptr)
        {
            std::cout << "instert pos_ptr (" << setPositionable.size() << ")" <<std::endl;
            setPositionable.insert(pos_ptr);
        }
        void removePositionnable (Positionnable* pos_ptr)
        {
            setPositionable.erase(setPositionable.find(pos_ptr));
        }


        // les assesseurs sur les booléen
        bool isFranchissable   () const    { return franchissable;}
        bool getOccupe          () const    { return (setPositionable.size() != 0 );};
        void setOccupe          (bool boule){ occupe = boule;};

   private :
        // la definition meme d'un case
        int i,j;

        // on peut pas stocke des pointeurs, ni des indice car les pointeurs volent en cas d'ajout et
        // les indices sont invalidés en cas de suppression
        // on doit stocker les coordonnées des voisins et passer par la map : du coup l'interet du tableau
        // est fortement limité
        /// EDIT : now il y a pas de modif de terrain in game so, ok :)
        std::array<Case*,6> voisin;
        bool franchissable;
        bool occupe;

        std::set<Positionnable*> setPositionable;


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



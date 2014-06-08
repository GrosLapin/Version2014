#include "utilitaire.hpp"
#include "../metier/terrain/terrain.hpp"
#include "../metier/terrain/case.hpp"

Terrain loadMap(std::string p_fichier)
{

    std::ifstream fichier(p_fichier.c_str(), std::ios::in );  // on ouvre en lecture
    std::vector<std::pair<int,int>> temp;
    if(fichier)  // si l'ouverture a fonctionné
    {
        std::string line;  // déclaration d'une chaîne qui contiendra la ligne lue

        while(getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
        {
            std::istringstream iss;
            iss.str(line);
            std::string i, j;
            iss >> i >> j ;

            temp.push_back(std::pair<int,int>(std::atoi(i.c_str()), std::atoi(j.c_str())));

        }
        fichier.close();
    }

    std::cout << temp.size() << std::endl;

    return Terrain(temp);
}


/// bug sans raison
bool saveMap(Terrain &terrain, std::string p_fichier)
{

    std::cout << "oui oui oiuoui ";
    std::ofstream fichier(p_fichier.c_str(),  std::ios_base::trunc );  //déclaration du flux et ouverture du fichier
    if(fichier)  // si l'ouverture a réussi
    {

        for ( Case& caseRef : terrain  )
        {
            fichier << caseRef.getI() << " " << caseRef.getJ() <<std::endl;

        }

        fichier.close();  // on referme le fichier
        return true;
    }

    return false;

}

std::string getDossier(std::string cheminExe)
{
    int possition = cheminExe.find_last_of("/\\");
    return  cheminExe.substr(0,possition) +"/";
}

std::vector<sf::Vector2f> getAllPoints(const sf::RenderWindow& cs)
{
    std::vector<sf::Vector2f> retour;

    retour.emplace_back(0,0);
    retour.emplace_back(0,cs.getSize().y);
    retour.emplace_back(cs.getSize().x,cs.getSize().y);
    retour.emplace_back(cs.getSize().x,0);

    return retour;
}


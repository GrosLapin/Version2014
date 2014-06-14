#ifndef PORTE_HPP
#define PORTE_HPP

class Porte
{
    public :
        /// a récupere de TD2013
        Porte (int forme, int range) ;

        std::vector<std::paire<int,int>> getZoneVirturelle ();
        int getRange () { return range; }
        int getForme () { return forme; }
    private :
        std::vector<std::paire<int,int>> zoneVirtuelle;
        int range;
        int forme;
};
#endif

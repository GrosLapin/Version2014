#ifndef ENUM_HPP
#define ENUM_HPP

enum Direction
{
    Est  =0 ,
    NordEst = 1,
    NordOuest =2,
    Ouest = 3,
    SudOuest =4,
    SudEst = 5,
    DebutDirection = Est,
    FinDirection = SudEst
};

Direction directionOppose (const Direction &p_dir);
void IJvoisin (const Direction&  p_dir, int& i, int& j);

#endif


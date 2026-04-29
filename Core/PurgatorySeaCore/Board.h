#pragma once
#include <vector>

#include "Position.h"

class FBoard
{
    
    std::vector<FPosition> PlayerShips;
    int Height;
    int Width;
    
    public:
    FBoard();

    void InitPlayerBoard();
    void SetHeightAndWidth(int NewHeight, int NewWidth);

    bool PlaceShip(FPosition Position);
    
    std::vector<FPosition> GetPlayerBoard();
};

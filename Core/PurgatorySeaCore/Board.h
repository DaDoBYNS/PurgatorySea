#pragma once
#include <vector>

#include "Position.h"
#include <memory>

#include "Ship.h"

class FBoard
{
    std::vector<std::shared_ptr<FShip>> Ships;
    std::vector<FPosition> PlayerShips;
    int Height;
    int Width;
    
    public:
    FBoard();

    void InitPlayerBoard();
    void SetHeightAndWidth(int NewHeight, int NewWidth);

    bool PlaceShip(FPosition Position);
    std::shared_ptr<FShip> CreateShip(FPosition InPosition, int InDimension); 
        
    std::vector<std::shared_ptr<FShip>> GetShips();
    
    std::vector<FPosition> GetPlayerBoard();
    
};

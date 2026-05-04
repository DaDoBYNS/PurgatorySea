#pragma once
#include <vector>

#include "Position.h"
#include <memory>

#include "Ship.h"

class FBoard
{
    std::vector<std::shared_ptr<FShip>> Ships;
    int Height;
    int Width;
    
    public:
    FBoard();

    void InitPlayerBoard();

    std::shared_ptr<FShip> CreateShip(FPosition InPosition, int InDimension, const char* InName); 
    
    void SetHeightAndWidth(int NewHeight, int NewWidth);
    
    std::vector<std::shared_ptr<FShip>> GetShips();
    int GetHeight() const;
    int GetWidth() const;
};

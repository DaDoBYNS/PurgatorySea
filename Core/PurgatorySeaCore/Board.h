#pragma once
#include <memory>
#include <vector>

#include "Ship.h"

class FBoard
{
    std::vector<std::shared_ptr<FShip>> Ships;
public:
    FBoard();

    std::shared_ptr<FShip> CreateShip(FPosition InPosition, int InDimension); 
    
    // Getter 
    std::vector<std::shared_ptr<FShip>> GetShips();
    
    // Setter
    
};

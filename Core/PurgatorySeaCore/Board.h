#pragma once
#include <memory>
#include <vector>

#include "Ship.h"

class FBoard
{
    std::vector<std::shared_ptr<FShip>> Ships;
public:
    FBoard();
    
    void CreateShip(FPosition InPosition); 
    
    // Getter 
    std::vector<std::shared_ptr<FShip>> GetShips();
    
    // Setter
    
};

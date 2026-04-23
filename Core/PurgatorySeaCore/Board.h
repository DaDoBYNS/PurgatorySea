#pragma once
#include <memory>
#include <vector>

#include "Ship.h"

class FBoard
{
    std::shared_ptr<FShip> Ship;
public:
    FBoard();
    
    // Getter 
    std::shared_ptr<FShip> GetShip();
    
    // Setter
    
};

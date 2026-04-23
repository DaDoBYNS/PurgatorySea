#pragma once
#include <memory>

#include "Board.h"
#include "Position.h"
#include "Ship.h"

class FSelection
{
    std::shared_ptr<FBoard> Board; 
public:
    FSelection();
    
    // Getter
    std::shared_ptr<FShip> GetShipAt(FPosition InPosition) const;

    // Setter
    void SetBoard(std::shared_ptr<FBoard> InBoard); 
};

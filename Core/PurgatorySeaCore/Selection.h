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
    std::shared_ptr<FShip> GetShipAt(FPosition InPosition) const;
};

#pragma once
#include <memory>

#include "Board.h"
#include "Position.h"
#include "Ship.h"

class FSelection
{
    std::shared_ptr<FBoard> Board; 
    std::shared_ptr<FShip> SelectedShip; 
public:
    FSelection();
    
    void MoveShipTo(FPosition InPosition) const;
    
    void RotateSelectedShip() const;
    std::shared_ptr<FShip> SelectShipAt(FPosition InPosition);
    
    std::shared_ptr<FShip> GetSelectedShip() const; 

    void SetBoard(std::shared_ptr<FBoard> InBoard);
    void SetSelectedShip(std::shared_ptr<FShip> InSelectedShip);
};

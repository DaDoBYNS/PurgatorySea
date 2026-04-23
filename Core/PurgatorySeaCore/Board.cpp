#include "Board.h"

FBoard::FBoard()
{
    Ship = std::make_shared<FShip>();
}

std::shared_ptr<FShip> FBoard::GetShip()
{
    return Ship; 
}

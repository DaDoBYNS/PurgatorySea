#include "Board.h"

FBoard::FBoard()
{
}

void FBoard::CreateShip(FPosition InPosition)
{
    Ships.emplace_back(std::make_shared<FShip>(InPosition)); 
}

std::vector<std::shared_ptr<FShip>> FBoard::GetShips()
{
    return Ships;
}

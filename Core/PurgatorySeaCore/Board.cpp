#include "Board.h"

FBoard::FBoard()
{
}

std::shared_ptr<FShip> FBoard::CreateShip(FPosition InPosition, int InDimension)
{
    Ships.emplace_back(std::make_shared<FShip>(InPosition, InDimension)); 
    return Ships.at(Ships.size() - 1); 
}

std::vector<std::shared_ptr<FShip>> FBoard::GetShips()
{
    return Ships;
}

#include "Board.h"

FBoard::FBoard()
{
}

void FBoard::CreateShip(int InDimension)
{
    Ships.emplace_back(std::make_shared<FShip>(InDimension)); 
}

std::vector<std::shared_ptr<FShip>> FBoard::GetShips()
{
    return Ships;
}

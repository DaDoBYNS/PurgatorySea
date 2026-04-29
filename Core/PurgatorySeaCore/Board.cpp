#include "Board.h"


FBoard::FBoard()
{
    Width = 10;
    Height = 10;
}

void FBoard::InitPlayerBoard()
{
    Ships.clear();
}

std::shared_ptr<FShip> FBoard::CreateShip(FPosition InPosition, int InDimension)
{
    Ships.emplace_back(std::make_shared<FShip>(InPosition, InDimension)); 
    return Ships.at(Ships.size() - 1); 
}

void FBoard::SetHeightAndWidth(int NewHeight, int NewWidth)
{
    Width = NewWidth;
    Height = NewHeight;

    Ships.clear();
}

std::vector<std::shared_ptr<FShip>> FBoard::GetShips()
{
    return Ships;
}

int FBoard::GetHeight() const
{
    return Height;
}

int FBoard::GetWidth() const
{
    return Width;
}

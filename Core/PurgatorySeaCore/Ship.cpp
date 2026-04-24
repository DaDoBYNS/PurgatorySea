#include "Ship.h"

FShip::FShip(FPosition InPosition, int InDimension)
    : bIsSelected(false)
    , Dimension(InDimension)
{
    for (int Y = 0; Y < Dimension; Y++)
    {
        int Number = static_cast<int>(InPosition.Number); 
        SetPosition(FPosition{InPosition.Letter, static_cast<ENumber>(Number-Y)}); 
    }
}

bool FShip::GetIsSelected() const
{
    return bIsSelected;
}

std::vector<FPosition> FShip::GetPositions() const
{
    return Positions; 
}

int FShip::GetDimension() const
{
    return Dimension;
}

FPosition FShip::GetFirstPosition() const
{
    return Positions.front();
}

void FShip::SetDimension(int InDimension)
{
    Dimension = InDimension;
}

void FShip::SetPosition(FPosition InPosition)
{
    Positions.emplace_back(InPosition);
}

void FShip::SetIsSelected(bool bInIsSelected)
{
    bIsSelected = bInIsSelected;
}

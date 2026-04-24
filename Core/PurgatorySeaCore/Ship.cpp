#include "Ship.h"

FShip::FShip(FPosition InPosition)
    : bIsSelected(false)
    , Dimension(0)
{
    SetPosition(InPosition); 
}

FShip::FShip(int InDimension)
    : bIsSelected(false)
    , Dimension(InDimension)
{
    for (int Y = 0; Y < Dimension; Y++)
    {
        SetPosition(FPosition{ELetter::A, static_cast<ENumber>(Y)}); 
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

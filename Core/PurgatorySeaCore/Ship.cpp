#include "Ship.h"

FShip::FShip(FPosition InPosition, int InDimension)
    : bIsSelected(false)
    , bIsErrorHighlighted(false)
    , Dimension(InDimension)
    , Name("null") 
{
    for (int Y = 0; Y < Dimension; Y++)
    {
        int Number = InPosition.Number; 
        SetPosition(FPosition{InPosition.Letter, Number-Y}); 
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

bool FShip::GetIsErrorHighlighted() const
{
    return bIsErrorHighlighted; 
}

std::string FShip::GetName() const
{
    return Name; 
}

void FShip::SetIsSelected(bool bInIsSelected)
{
    bIsSelected = bInIsSelected;
}

void FShip::SetPositions(std::vector<FPosition> InPositions)
{
    Positions = InPositions;
}

void FShip::SetDimension(int InDimension)
{
    Dimension = InDimension;
}

void FShip::SetPosition(FPosition InPosition)
{
    Positions.emplace_back(InPosition);
}

void FShip::SetIsErrorHighlighted(bool bInIsErrorHighlighted)
{
    bIsErrorHighlighted = bInIsErrorHighlighted;
}

void FShip::SetName(std::string InName)
{
    Name = InName;
}

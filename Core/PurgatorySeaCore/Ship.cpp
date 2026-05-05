#include "Ship.h"

void FShip::GeneratePositionsFromFirstPosition(FPosition InFirstPosition)
{
    Positions.clear();

    for (int Index = 0; Index < Dimension; Index++)
    {
        if (Rotation == ERotation::Vertical)
        {
            Positions.emplace_back(FPosition{
                InFirstPosition.Letter,
                InFirstPosition.Number - Index
            });
        }
        else if (Rotation == ERotation::Horizontal)
        {
            Positions.emplace_back(FPosition{
                InFirstPosition.Letter - Index,
                InFirstPosition.Number
            });
        }
    }
}

FShip::FShip(FPosition InPosition, int InDimension)
    : bIsSelected(false)
    , bIsErrorHighlighted(false)
    , Dimension(InDimension)
    , Name("null") 
    , Rotation(ERotation::Vertical)
{
    /*for (int Y = 0; Y < Dimension; Y++)
    {
        int Number = InPosition.Number; 
        SetPosition(FPosition{InPosition.Letter, Number-Y}); 
    }*/
    GeneratePositionsFromFirstPosition(InPosition);
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

ERotation FShip::GetRotation() const
{
    return Rotation; 
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

void FShip::SetRotation(ERotation InRotation)
{
    FPosition FirstPosition = Positions.front();
    Rotation = InRotation;

    GeneratePositionsFromFirstPosition(FirstPosition);
}

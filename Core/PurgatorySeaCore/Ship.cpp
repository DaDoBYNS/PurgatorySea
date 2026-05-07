#include "Ship.h"

FShip::FShip(FPosition InPosition, int InDimension)
    : bIsSelected(false)
    , bIsErrorHighlighted(false)
    , bIsSunk(false)
    , Name("null")
    , Rotation(ERotation::Vertical)
    , Dimension(InDimension)
{
    GeneratePositionsFromFirstPosition(InPosition);
}

void FShip::GeneratePositionsFromFirstPosition(FPosition InFirstPosition)
{
    Positions.clear();
    HitPositions.clear();
    bIsSunk = false;

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

bool FShip::ContainsPosition(FPosition InPosition) const
{
    for (const auto& Position : Positions)
    {
        if (Position == InPosition)
        {
            return true;
        }
    }

    return false;
}

bool FShip::HasHitPosition(FPosition InPosition) const
{
    for (const auto& HitPosition : HitPositions)
    {
        if (HitPosition == InPosition)
        {
            return true;
        }
    }

    return false;
}

bool FShip::RegisterHit(FPosition InPosition)
{
    if (!ContainsPosition(InPosition))
    {
        return false;
    }

    if (HasHitPosition(InPosition))
    {
        return false;
    }

    HitPositions.emplace_back(InPosition);

    if (HitPositions.size() == Positions.size())
    {
        bIsSunk = true;
    }

    return true;
}

bool FShip::GetIsSelected() const
{
    return bIsSelected;
}

std::vector<FPosition> FShip::GetPositions() const
{
    return Positions;
}

std::vector<FPosition> FShip::GetHitPositions() const
{
    return HitPositions;
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

bool FShip::GetIsSunk() const
{
    return bIsSunk;
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

void FShip::SetIsSunk(bool bInIsSunk)
{
    bIsSunk = bInIsSunk;
}
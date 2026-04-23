#include "Ship.h"

FShip::FShip()
    : bIsSelected(false)
    , Position(FPosition{ELetter::A, ENumber::Four})
{}

bool FShip::GetIsSelected() const
{
    return bIsSelected;
}

FPosition FShip::GetPosition() const
{
    return Position; 
}

void FShip::SetIsSelected(bool bInIsSelected)
{
    bIsSelected = bInIsSelected;
}

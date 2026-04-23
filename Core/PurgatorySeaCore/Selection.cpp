#include "Selection.h"

#include "Position.h"

FSelection::FSelection()
{
    Board = std::make_shared<FBoard>();
}

std::shared_ptr<FShip> FSelection::GetShipAt(FPosition InPosition) const
{
    if (Board->GetShip()->GetPosition().Letter == InPosition.Letter && 
        Board->GetShip()->GetPosition().Number == InPosition.Number)
    {
        Board->GetShip()->SetIsSelected(true);
        return Board->GetShip();   
    }
    return nullptr;
}

#include "Selection.h"

#include "Position.h"

FSelection::FSelection()
{}

std::shared_ptr<FShip> FSelection::GetShipAt(FPosition InPosition) const
{
    if (Board)
    {
        for (const auto& Ship : Board->GetShips())
        {
            for (const auto Position : Ship->GetPositions())
            {
                if (Position.Letter == InPosition.Letter && Position.Number == InPosition.Number)
                {
                    Ship->SetIsSelected(true);
                    return Ship; 
                }
            }
        }
        
        /*for (const auto Position : Board->GetShip(0)->GetPositions())
        {
            if (Position.Letter == InPosition.Letter && Position.Number == InPosition.Number)
            {
                Board->GetShip(0)->SetIsSelected(true);
                return Board->GetShip(0);
            }
        }*/
    }
    return nullptr;
}

void FSelection::SetBoard(std::shared_ptr<FBoard> InBoard)
{
    Board = InBoard; 
}

#include "Selection.h"

#include "Position.h"

FSelection::FSelection()
    : Board(nullptr)
    , SelectedShip(nullptr) 
{}

std::shared_ptr<FShip> FSelection::SelectShipAt(FPosition InPosition)
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
                    SelectedShip = Ship; 
                    return SelectedShip; 
                }
            }
        }
    }
    return nullptr;
}

std::shared_ptr<FShip> FSelection::GetSelectedShip() const
{
    return SelectedShip;
}

void FSelection::SetBoard(std::shared_ptr<FBoard> InBoard)
{
    Board = InBoard; 
}

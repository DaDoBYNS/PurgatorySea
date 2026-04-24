#include "Selection.h"

#include "Position.h"

FSelection::FSelection()
    : Board(nullptr)
    , SelectedShip(nullptr) 
{}

void FSelection::MoveShipTo(FPosition InPosition)
{
    auto ShipPositions = SelectedShip->GetPositions();
    for (int Index = 0; Index < SelectedShip->GetDimension(); Index++)
    {
        ShipPositions[Index] = FPosition{InPosition.Letter, InPosition.Number-Index}; 
    }
    
    SelectedShip->SetPositions(ShipPositions);
}

std::shared_ptr<FShip> FSelection::SelectShipAt(FPosition InPosition)
{
    if (SelectedShip)
    {
        SelectedShip->SetIsSelected(false);
    }
    
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
    
    SelectedShip = nullptr;
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

#include "GameController.h"

FGameController::FGameController()
    : bIsGameReady(false)
{}

void FGameController::InitGame()
{
    Board->CreateShip(FPosition{ELetter::A, ENumber::Eight}, 2, "null");
    Board->CreateShip(FPosition{ELetter::B, ENumber::Eight}, 3, "null");
    Board->CreateShip(FPosition{ELetter::C, ENumber::Eight}, 3, "null");
    Board->CreateShip(FPosition{ELetter::D, ENumber::Eight}, 4, "battleship");
    Board->CreateShip(FPosition{ELetter::E, ENumber::Eight}, 5, "aircraft carrier");
    
    bIsGameReady = true;
}

std::shared_ptr<FShip> FGameController::SelectShipAt(FPosition InPosition) const
{
    return Selection->SelectShipAt(InPosition);
}

std::shared_ptr<FShip> FGameController::SelectShipByName(std::string InName) const
{
    for (auto Ship : Board->GetShips())
    {
        if (Ship->GetName() == InName)
        {
            Ship->SetIsSelected(true);
            Selection->SetSelectedShip(Ship); 
            return Ship;
        }
    }
    
    return nullptr;
}

void FGameController::MoveShipTo(FPosition InPosition) const
{
    Selection->MoveShipTo(InPosition);
}

void FGameController::SetBoard(std::shared_ptr<FBoard>& InBoard)
{
    Board = InBoard;
}

void FGameController::SetSelection(std::shared_ptr<FSelection>& InSelection)
{
    Selection = InSelection;    
}

std::shared_ptr<FBoard> FGameController::GetBoard() const
{
    return Board;
}

std::shared_ptr<FSelection> FGameController::GetSelection() const
{
    return Selection; 
}

bool FGameController::GetIsGameReady() const
{
    return bIsGameReady; 
}

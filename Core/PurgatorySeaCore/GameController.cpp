#include "GameController.h"

FGameController::FGameController()
    : bIsGameReady(false)
{
}

void FGameController::InitGame()
{
    Board->CreateShip(FPosition{ELetter::A, ENumber::Eight}, 2, "torpedo");
    Board->CreateShip(FPosition{ELetter::B, ENumber::Eight}, 3, "submarine");
    Board->CreateShip(FPosition{ELetter::C, ENumber::Eight}, 3, "swiftboat");
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
    if (Selection->GetSelectedShip())
    {
        Selection->GetSelectedShip()->SetIsSelected(false);
    }

    for (auto Ship : Board->GetShips())
    {
        if (Ship->GetName() == InName)
        {
            Ship->SetIsSelected(true);
            Selection->SetSelectedShip(Ship);

            return Ship;
        }
    }

    Selection->SetSelectedShip(nullptr);
    return nullptr;
}

void FGameController::MoveShipTo(FPosition InPosition) const
{
    Selection->MoveShipTo(InPosition);
}

void FGameController::RotateSelectedShip() const
{
    if (Selection == nullptr)
    {
        return;
    }

    Selection->RotateSelectedShip();
}

void FGameController::EmptySelectedShip() const
{
    if (!Selection->GetSelectedShip())
    {
        return;
    }

    Selection->GetSelectedShip()->SetIsSelected(false);
    Selection->SetSelectedShip(nullptr);
}

bool FGameController::IsShotPositionValid(FPosition ShotPosition) const
{
    return ShotPosition.Letter >= static_cast<int>(ELetter::A)
        && ShotPosition.Letter <= static_cast<int>(ELetter::J)
        && ShotPosition.Number >= static_cast<int>(ENumber::One)
        && ShotPosition.Number <= static_cast<int>(ENumber::Ten);
}

EHitStatus FGameController::ReceiveShot(FPosition ShotPosition)
{
    if (!IsShotPositionValid(ShotPosition))
    {
        return EHitStatus::AlredyShot;
    }

    if (Board == nullptr)
    {
        return EHitStatus::Miss;
    }

    return Board->ReceiveShot(ShotPosition);
}

EHitStatus FGameController::RegisterEnemyBoardShot(FPosition ShotPosition, EHitStatus ShotResult)
{
    if (!IsShotPositionValid(ShotPosition))
    {
        return EHitStatus::AlredyShot;
    }

    return EnemyBoard.SetHitPosition(ShotPosition, ShotResult);
}

bool FGameController::HasWon() const
{
    if (Board == nullptr)
    {
        return false;
    }

    int TotalShips = static_cast<int>(Board->GetShips().size());

    if (TotalShips <= 0)
    {
        return false;
    }

    return EnemyBoard.GetSunkShipsCount() >= TotalShips;
}

bool FGameController::HasLost() const
{
    if (Board == nullptr)
    {
        return false;
    }

    return Board->AreAllShipsSunk();
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

FEnemyBoard FGameController::GetEnemyBoard() const
{
    return EnemyBoard;
}
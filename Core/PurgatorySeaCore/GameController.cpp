#include "GameController.h"

FGameController::FGameController()
    : bIsGameReady(false)
{}

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
    if (!Selection->GetSelectedShip()) return; 
    
    Selection->GetSelectedShip()->SetIsSelected(false);
    Selection->SetSelectedShip(nullptr);
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


void FGameController::SetEnemyShipPositions(const std::vector<FPosition>& Positions)
{
    EnemyBoard.InitEnemyBoard();
    for (const auto& Position : Positions)
    {
        EnemyBoard.AddShipPosition(Position);
    }
}

bool FGameController::IsShotPositionValid(FPosition ShotPosition) const
{
    return ShotPosition.Letter >= static_cast<int>(ELetter::A) 
        && ShotPosition.Letter <= static_cast<int>(ELetter::J)
        && ShotPosition.Number >= static_cast<int>(ENumber::One) 
        && ShotPosition.Number <= static_cast<int>(ENumber::Ten);
}

EEnemyTileType FGameController::Shoot(FPosition ShotPosition)
{
    if (!IsShotPositionValid(ShotPosition))
        return EEnemyTileType::AlredyShot;
    
    return EnemyBoard.SetHitPosition(ShotPosition);
}


bool FGameController::HasWon() const
{
    auto ShipPositions = EnemyBoard.GetEnemyShipPositions();
    auto HitPositions = EnemyBoard.GetHitPositions();

    if (ShipPositions.empty())
        return false;

    for (const auto& ShipPosition : ShipPositions)
    {
        bool bWasHit = false;
        for (const auto& Hit : HitPositions)
        {
            if (Hit.Position == ShipPosition && Hit.Type == EEnemyTileType::Hit)
            {
                bWasHit = true;
                break;
            }
        }

        if (!bWasHit)
            return false;
    }

    return true;
}

FEnemyBoard FGameController::GetEnemyBoard()
{
    return EnemyBoard;
}

void FGameController::RegisterReceivedShot(FPosition ShotPosition)
{
    ReceivedShot.emplace_back(ShotPosition);
}

std::vector<FPosition> FGameController::GetReceivedShot()
{
    return ReceivedShot;
}


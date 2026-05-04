#include "GameController.h"

FGameController::FGameController()
    : bIsGameReady(false)
{}

void FGameController::InitGame()
{
    Board->CreateShip(FPosition{ELetter::A, ENumber::Eight}, 2, "null");
    Board->CreateShip(FPosition{ELetter::B, ENumber::Eight}, 3, "submarine");
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

void FGameController::SetPlayerShipPositions(const std::vector<FPosition>& Positions)
{
    if (GetPlayer1ShipPositions().GetEnemyShipPositions().empty())
    {
        SetPlayer1ShipPositions(Positions);
    }
    else
    {
        SetPlayer2ShipPositions(Positions);
    }
}

void FGameController::SetPlayer1ShipPositions(const std::vector<FPosition>& Positions)
{
    Player1Board.InitEnemyBoard();
    for (const auto& Position : Positions)
    {
        Player1Board.AddShipPosition(Position);
    }
}

void FGameController::SetPlayer2ShipPositions(const std::vector<FPosition>& Positions)
{
    Player2Board.InitEnemyBoard();
    for (const auto& Position : Positions)
    {
        Player2Board.AddShipPosition(Position);
    }
}

EEnemyTileType FGameController::Player1Shoot(FPosition ShotPosition)
{
    return Player2Board.SetHitPosition(ShotPosition);
}

EEnemyTileType FGameController::Player2Shoot(FPosition ShotPosition)
{
    return Player1Board.SetHitPosition(ShotPosition);
}

bool FGameController::HasWon(const FEnemyBoard& EnemyBoard)
{
    auto ShipPositions = EnemyBoard.GetEnemyShipPositions();
    auto HitPositions = EnemyBoard.GetHitPositions();

    if (ShipPositions.empty())
    {
        return false;
    }

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
        {
            return false;
        }
    }

    return true;
}


int FGameController::CheckWinner()
{    
    if (HasWon(Player2Board))
    {
        return 1;
    }

    if (HasWon(Player1Board))
    {
        return 2;
    }

    return 0;
}

FEnemyBoard FGameController::GetPlayer1ShipPositions()
{
    return Player1Board;
}

FEnemyBoard FGameController::GetPlayer2ShipPositions()
{
    return Player2Board;
}


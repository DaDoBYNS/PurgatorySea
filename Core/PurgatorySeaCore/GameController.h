#pragma once
#include <string>

#include "Board.h"
#include "Selection.h"
#include "EnemyBoard.h"

class FGameController
{
    std::shared_ptr<FBoard> Board;
    std::shared_ptr<FSelection> Selection;
    
    bool bIsGameReady;
    FEnemyBoard Player1Board;
    FEnemyBoard Player2Board;
    
public:
    FGameController();
    void InitGame();
    std::shared_ptr<FShip> SelectShipAt(FPosition InPosition) const;
    std::shared_ptr<FShip> SelectShipByName(std::string InName) const;
    void MoveShipTo(FPosition InPosition) const;
    void SetBoard(std::shared_ptr<FBoard>& InBoard);
    void SetSelection(std::shared_ptr<FSelection>& InSelection);
    std::shared_ptr<FBoard> GetBoard() const;
    std::shared_ptr<FSelection> GetSelection() const;
    bool GetIsGameReady() const;

    void SetPlayerShipPositions(const std::vector<FPosition>& Positions);
    void SetPlayer1ShipPositions(const std::vector<FPosition>& Positions);
    void SetPlayer2ShipPositions(const std::vector<FPosition>& Positions);
    
    bool IsShotPositionValid(FPosition InPosition) const;
    EEnemyTileType Player1Shoot(FPosition ShotPosition);
    EEnemyTileType Player2Shoot(FPosition ShotPosition);
    
    bool HasWon(const FEnemyBoard& EnemyBoard);
    int CheckWinner();

    FEnemyBoard GetPlayer1ShipPositions();
    FEnemyBoard GetPlayer2ShipPositions();
};

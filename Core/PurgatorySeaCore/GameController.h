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
    FEnemyBoard EnemyBoard;
    std::vector<FPosition> ReceivedShot;
    
    
public:
    FGameController();
    void InitGame();
    
    std::shared_ptr<FShip> SelectShipAt(FPosition InPosition) const;
    std::shared_ptr<FShip> SelectShipByName(std::string InName) const;
    
    void MoveShipTo(FPosition InPosition) const;
    void RotateSelectedShip() const;
    
    bool IsShotPositionValid(FPosition InPosition) const;
    void EmptySelectedShip() const;
    
    EHitStatus Shoot(FPosition ShotPosition);
    
    bool HasWon() const;
    
    void SetBoard(std::shared_ptr<FBoard>& InBoard);
    void SetSelection(std::shared_ptr<FSelection>& InSelection);
    void SetEnemyShipPositions(const std::vector<FPosition>& Positions);
    
    std::shared_ptr<FBoard> GetBoard() const;
    std::shared_ptr<FSelection> GetSelection() const;
    bool GetIsGameReady() const;
    FEnemyBoard GetEnemyBoard();
    void RegisterReceivedShot(FPosition ShotPosition);
    std::vector<FPosition> GetReceivedShot();
};

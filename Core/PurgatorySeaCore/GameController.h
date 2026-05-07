#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Board.h"
#include "EnemyBoard.h"
#include "Selection.h"

class FGameController
{
    std::shared_ptr<FBoard> Board;
    std::shared_ptr<FSelection> Selection;

    bool bIsGameReady;
    FEnemyBoard EnemyBoard;

public:
    FGameController();

    void InitGame();

    std::shared_ptr<FShip> SelectShipAt(FPosition InPosition) const;
    std::shared_ptr<FShip> SelectShipByName(std::string InName) const;

    void MoveShipTo(FPosition InPosition) const;
    void RotateSelectedShip() const;

    bool IsShotPositionValid(FPosition InPosition) const;

    void EmptySelectedShip() const;

    EHitStatus ReceiveShot(FPosition ShotPosition);
    EHitStatus RegisterEnemyBoardShot(FPosition ShotPosition, EHitStatus ShotResult);

    bool HasWon() const;
    bool HasLost() const;
    
    void SetBoard(std::shared_ptr<FBoard>& InBoard);
    void SetSelection(std::shared_ptr<FSelection>& InSelection);

    std::shared_ptr<FBoard> GetBoard() const;
    std::shared_ptr<FSelection> GetSelection() const;

    bool GetIsGameReady() const;

    FEnemyBoard GetEnemyBoard() const;
};
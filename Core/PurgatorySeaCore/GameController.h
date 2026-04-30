#pragma once
#include "Board.h"
#include "Selection.h"

class FGameController
{
    std::shared_ptr<FBoard> Board;
    std::shared_ptr<FSelection> Selection;
    
    bool bIsGameReady;
    
public:
    FGameController();
    void InitGame();
    std::shared_ptr<FShip> SelectShipAt(FPosition InPosition) const;
    void SetBoard(std::shared_ptr<FBoard>& InBoard);
    void SetSelection(std::shared_ptr<FSelection>& InSelection);
    std::shared_ptr<FBoard> GetBoard() const;
    std::shared_ptr<FSelection> GetSelection() const;
    bool GetIsGameReady() const;
};

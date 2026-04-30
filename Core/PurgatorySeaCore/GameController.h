#pragma once
#include "Board.h"
#include "Selection.h"

class FGameController
{
    std::shared_ptr<FBoard> Board;
    std::shared_ptr<FSelection> Selection;
    
public:
    FGameController();
    void SetBoard(std::shared_ptr<FBoard>& InBoard);
    void SetSelection(std::shared_ptr<FSelection>& InSelection);
    std::shared_ptr<FBoard> GetBoard();
    std::shared_ptr<FSelection> GetSelection();
};

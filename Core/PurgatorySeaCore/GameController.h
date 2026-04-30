#pragma once
#include "Board.h"

class FGameController
{
    std::shared_ptr<FBoard> Board;
    
public:
    FGameController();
    void SetBoard(std::shared_ptr<FBoard>& InBoard);
    std::shared_ptr<FBoard> GetBoard();
};

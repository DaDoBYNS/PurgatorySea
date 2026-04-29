#pragma once
#include "Board.h"

class FValidation
{
    std::shared_ptr<FBoard> Board; 
    bool bIsValid; 
public:
    FValidation();
    void ValidateShips();
    void SetBoard(std::shared_ptr<FBoard> InBoard);
    bool GetIsValid();
};

#pragma once
#include "Letter.h"
#include "Number.h"

struct FPosition
{
    int Letter;
    int Number;
    
    friend bool operator==(const FPosition& lhs, const FPosition& rhs)
    {
        return lhs.Letter == rhs.Letter
            && lhs.Number == rhs.Number;
    }

    friend bool operator!=(const FPosition& lhs, const FPosition& rhs)
    {
        return !(lhs == rhs);
    }
    
    FPosition(ELetter InLetter, ENumber InNumber)
        : Letter(static_cast<int>(InLetter)),
          Number(static_cast<int>(InNumber))
    {
    }

    FPosition(int InLetter, int InNumber)
        : Letter(InLetter),
          Number(InNumber)
    {
    }
    
    FPosition(ELetter InLetter, int InNumber)
        : Letter(static_cast<int>(InLetter)),
          Number(InNumber)
    {
    }
    
    FPosition(int InLetter, ENumber InNumber)
        : Letter(InLetter),
          Number(static_cast<int>(InNumber))
    {
    }
    
};
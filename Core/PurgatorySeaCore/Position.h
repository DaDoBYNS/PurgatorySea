#pragma once
#include "Letter.h"
#include "Number.h"

struct FPosition
{
    ELetter Letter;
    ENumber Number;
    
    bool operator==(const FPosition& Other) const
    {
        return Letter == Other.Letter && Number == Other.Number;
    }
};
 
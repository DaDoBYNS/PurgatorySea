#pragma once
#include "Letter.h"
#include "Number.h"

struct FPosition
{
    friend bool operator==(const FPosition& lhs, const FPosition& rhs)
    {
        return lhs.Letter == rhs.Letter
            && lhs.Number == rhs.Number;
    }

    friend bool operator!=(const FPosition& lhs, const FPosition& rhs)
    {
        return !(lhs == rhs);
    }

    ELetter Letter;
    ENumber Number;
};

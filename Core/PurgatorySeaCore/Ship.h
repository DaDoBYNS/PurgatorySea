#pragma once
#include <vector>

#include "Position.h"

class FShip
{
    bool bIsSelected;
    FPosition Position; 
public:
    FShip();
    
    // Getter
    bool GetIsSelected() const;
    FPosition GetPosition() const;

    // Setter
    void SetIsSelected(bool bInIsSelected);
};

#pragma once
#include <vector>

#include "Position.h"

class FShip
{
    bool bIsSelected;
    std::vector<FPosition> Positions; 
    int Dimension; 
public:
    FShip();
    FShip(int InDimension);
    
    // Getter
    bool GetIsSelected() const;
    std::vector<FPosition> GetPositions() const;
    int GetDimension() const;

    // Setter
    void SetIsSelected(bool bInIsSelected);
    void SetDimension(int InDimension);
    void SetPosition(FPosition InPosition);
};

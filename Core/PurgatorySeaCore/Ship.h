#pragma once
#include <vector>

#include "Position.h"

class FShip
{
    bool bIsSelected;
    std::vector<FPosition> Positions; 
    int Dimension; 
public:
    FShip(FPosition InPosition, int InDimension);
    
    // Getter
    bool GetIsSelected() const;
    std::vector<FPosition> GetPositions() const;
    int GetDimension() const;
    FPosition GetFirstPosition() const;

    // Setter
    void SetIsSelected(bool bInIsSelected);
    void SetPositions(std::vector<FPosition> InPositions);
    void SetDimension(int InDimension);
    void SetPosition(FPosition InPosition);
};

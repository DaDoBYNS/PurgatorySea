#pragma once
#include <string>
#include <vector>

#include "Position.h"

class FShip
{
    bool bIsSelected;
    bool bIsErrorHighlighted;
    std::vector<FPosition> Positions; 
    std::string Name; 
    int Dimension; 
public:
    FShip(FPosition InPosition, int InDimension);
    
    // Getter
    bool GetIsSelected() const;
    std::vector<FPosition> GetPositions() const;
    int GetDimension() const;
    FPosition GetFirstPosition() const;
    bool GetIsErrorHighlighted() const;
    std::string GetName() const; 

    // Setter
    void SetIsSelected(bool bInIsSelected);
    void SetPositions(std::vector<FPosition> InPositions);
    void SetDimension(int InDimension);
    void SetPosition(FPosition InPosition);
    void SetIsErrorHighlighted(bool bInIsErrorHighlighted);
    void SetName(std::string InName);
};

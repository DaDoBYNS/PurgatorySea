#pragma once
#include <string>
#include <vector>

#include "Position.h"
#include "Rotation.h"

class FShip
{
    bool bIsSelected;
    bool bIsErrorHighlighted;
    bool bIsSunk;
    std::vector<FPosition> Positions;
    std::vector<FPosition> HitPositions;
    std::string Name;
    ERotation Rotation;
    int Dimension;

public:
    FShip(FPosition InPosition, int InDimension);

    void GeneratePositionsFromFirstPosition(FPosition InFirstPosition);

    bool ContainsPosition(FPosition InPosition) const;
    bool HasHitPosition(FPosition InPosition) const;
    bool RegisterHit(FPosition InPosition);

    bool GetIsSelected() const;
    std::vector<FPosition> GetPositions() const;
    std::vector<FPosition> GetHitPositions() const;
    int GetDimension() const;
    FPosition GetFirstPosition() const;
    bool GetIsErrorHighlighted() const;
    std::string GetName() const;
    ERotation GetRotation() const;
    bool GetIsSunk() const;

    void SetIsSelected(bool bInIsSelected);
    void SetPositions(std::vector<FPosition> InPositions);
    void SetDimension(int InDimension);
    void SetPosition(FPosition InPosition);
    void SetIsErrorHighlighted(bool bInIsErrorHighlighted);
    void SetName(std::string InName);
    void SetRotation(ERotation InRotation);
    void SetIsSunk(bool bInIsSunk);
};
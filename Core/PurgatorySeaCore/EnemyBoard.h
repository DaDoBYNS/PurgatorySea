#pragma once
#include <vector>

#include "HitStatus.h"
#include "Position.h"

struct SEnemyBoard
{
    FPosition Position;
    EHitStatus Type;
};

class FEnemyBoard
{
    std::vector<SEnemyBoard> HitPositions;

public:
    FEnemyBoard();

    void InitEnemyBoard();

    EHitStatus SetHitPosition(FPosition HitPosition, EHitStatus HitStatus);

    bool CheckShot(FPosition HitPosition) const;

    int GetSunkShipsCount() const;

    std::vector<SEnemyBoard> GetHitPositions() const;
};
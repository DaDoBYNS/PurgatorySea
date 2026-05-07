#pragma once
#include <vector>

#include "Position.h"
#include "HitStatus.h"

struct SEnemyBoard
{
    FPosition Position;
    EHitStatus Type;
};


class FEnemyBoard
{
    
    std::vector<FPosition> EnemyShipPosition;
    std::vector<SEnemyBoard> HitPositions;
    
public:
    FEnemyBoard();
    
    void InitEnemyBoard();
    
    bool AddShipPosition(FPosition ShipPosition);
    
    EHitStatus SetHitPosition(FPosition HitPosition);
    
    bool CheckShot(FPosition HitPosition);
    
    std::vector<FPosition> GetEnemyShipPositions() const;
    std::vector<SEnemyBoard> GetHitPositions() const;
};
